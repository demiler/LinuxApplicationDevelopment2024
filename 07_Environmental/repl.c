#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <rhash.h>

#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

#define MAX_BUFFER_LENGTH (1 << 16) - 1
#define MAX_HASH_LENGTH 256

const char PS1[] = "> ";

size_t prompt(char buffer[MAX_BUFFER_LENGTH]) {
#ifdef USE_READLINE
    char *readlined = readline(PS1);
    if (readlined == NULL) return -1;
    strncpy(buffer, readlined, MAX_BUFFER_LENGTH);
    free(readlined);
    return strlen(buffer);
#else
    printf(PS1);
    char *iseof = fgets(buffer, MAX_BUFFER_LENGTH, stdin);
    if (iseof == NULL) return -1;

    size_t chars_read = strlen(buffer);
    buffer[chars_read - 1] = '\0'; // remove '\n' from stdin
    return chars_read - 1;
#endif
}

void strlow(char *s) {
    for (char *p = s; *p; ++p) {
        *p = tolower(*p);
    }
}

size_t makeHash(char *hashName, char *data, int isFile, char *hash, int flags) {
    unsigned hashType = 0;
    if (strcmp(hashName, "md5") == 0)          { hashType = RHASH_MD5; }
    else if (strcmp(hashName, "sha1") == 0)    { hashType = RHASH_SHA1; }
    else if (strcmp(hashName, "tth") == 0)     { hashType = RHASH_TTH; }
    else if (strcmp(hashName, "sha256") == 0)  { hashType = RHASH_SHA256; }
    else {
        return -2;
    }

    int hashLen = rhash_get_hash_length(hashType);
    unsigned char *rawHash = (unsigned char*)malloc(hashLen);

    size_t success;
    if (isFile) {
        success = rhash_file(hashType, data, rawHash);
    }
    else {
        success = rhash_msg(hashType, data, strlen(data), rawHash);
    }

    if (success == -1) {
        free(rawHash);
        return -1;
    }

    int hashCharLen = rhash_print_bytes(hash, rawHash, rhash_get_digest_size(hashType), flags);
    free(rawHash);
    return hashCharLen;
}

int main(int argc, const char *argv[]) {
    rhash_library_init();
    char *command = NULL, *argument = NULL;
    char buffer[MAX_BUFFER_LENGTH];

    while (!command || strcmp(command, "exit") != 0) {
        size_t responseLen = prompt(buffer);
        if (responseLen == -1) break; // EOF
        if (responseLen == 0) continue; // empty input

        command = strtok_r(buffer, " ", &argument);
        if (*argument == '\0') {
            fprintf(stderr, "Error: empty argument\n");
            continue;
        }

        int needBase64 = islower(*command) > 0;
        strlow(command);

        int isFile = (argument[0] != '"');
        if (!isFile) ++argument;  // remove technical token

        char hash[MAX_HASH_LENGTH];
        size_t hashLen = makeHash(
            command, argument, isFile, hash,
            (needBase64 ? RHPR_BASE64 : RHPR_HEX)
        );
        if (hashLen == -1) {
            fprintf(stderr, "Error: unable to create hash. Reason: %s\n", strerror(errno));
        }
        else if (hashLen == -2) {
            fprintf(stderr, "Error: unknown hash '%s'\n", command);
        }
        else {
            printf("%s\n", hash);
        }
    }

    return 0;
}
