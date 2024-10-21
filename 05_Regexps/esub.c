#include <stdlib.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

#define MAX_CAP_GROUPS 9u
#define MAX_REFERENCES 100u
#define MAX_ERROR_BUFFER 1024u
#define REFERENCE_REGEX "\\\\[1-9]"

int getCaptureGroupId(const char* sub, regmatch_t match) {
    return sub[match.rm_eo - 1] - 48; // char to int from 0 to 9
}

int main(int argc, const char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <pattern> <substitution> <string>\n", argv[0]);
        return 0;
    }

    regex_t pattern, reference;

    int compfail = regcomp(&pattern, argv[1], REG_EXTENDED);
    if (compfail) {
        char errormsg[MAX_ERROR_BUFFER];
        regerror(compfail, &pattern, errormsg, MAX_ERROR_BUFFER);
        printf("Error: failed to compile regex. Reason: %s\n", errormsg);
        return 0;
    }
    regcomp(&reference, REFERENCE_REGEX, 0);

    const char* sub     = argv[2];
    const char* string  = argv[3];

    regmatch_t refpos[1], capgroups[MAX_CAP_GROUPS + 1];
    int ismatch = regexec(&pattern, string, MAX_CAP_GROUPS + 1, capgroups, 0);

    if (ismatch == REG_NOMATCH) {
        printf("%s\n", string);
    }
    else {
        const size_t inlen = strlen(string);
        const size_t sublen = strlen(sub);
        const char* const substart = sub;

        int success = 1;
        size_t max_size = inlen + sublen;
        while (regexec(&reference, sub, 1, refpos, 0) != REG_NOMATCH) {
            int capgrpid = getCaptureGroupId(sub, *refpos);
            regmatch_t capgrp = capgroups[capgrpid];
            if (capgrp.rm_so == -1) {
                printf("Error: capture group %d wasn't found!\n", capgrpid);
                success = 0;
                break;
            }
            size_t capgrplen = capgrp.rm_eo - capgrp.rm_so;
            max_size += capgrplen;
            sub += refpos->rm_eo;
        }
        sub = substart;

        if (success) {
            char* const out = (char* const)malloc(max_size + 1);

            //printf("%d %d\n", capgroups[0].rm_so, capgroups[0].rm_eo);
            strncpy(out, string, capgroups[0].rm_so);
            char* outptr = out + capgroups[0].rm_so;
            *outptr = 0;

            while (regexec(&reference, sub, 1, refpos, 0) != REG_NOMATCH) {
                int capgrpid = getCaptureGroupId(sub, *refpos);
                regmatch_t capgrp = capgroups[capgrpid];
                if (capgrp.rm_so == -1) {
                    printf("Error: capture group %d wasn't found!\n", capgrpid);
                    break;
                }
                //printf("%d %d %d\n", refpos->rm_so, refpos->rm_eo, capgrpid);

                size_t caplen = capgrp.rm_eo - capgrp.rm_so;
                strncpy(outptr, sub, refpos->rm_so);
                outptr += refpos->rm_so;
                strncpy(outptr, string + capgrp.rm_so, caplen);
                outptr += caplen;
                *outptr = 0;
                sub += refpos->rm_eo;
            }

            if (sub) {
                size_t subtaillen = sublen - (sub - substart);
                strncpy(outptr, sub, subtaillen);
                outptr += subtaillen;
                *outptr = 0;
            }

            size_t taillen = inlen - capgroups[0].rm_eo;
            strncpy(outptr, string + capgroups[0].rm_eo, taillen);
            *(outptr + taillen) = 0;

            printf("%s\n", out);
            free(out);
        }
    }

    regfree(&reference);
    regfree(&pattern);

    return 0;
}
