#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include "calc.h"

#include "../config.h"

#define MAX_NUMBERS 255
/**< Defines max memory usage for the program. Very memory safe! **/

#define _(STRING) gettext(STRING)

/** Prints help message
  *
  */
void help() {
    printf(_("Usage: avg [<options>]\n"));
    printf(_("  Calculates average of your input. Very usefull!\n"));
    printf("\n");
    printf(_("Options:\n"));
    printf(_("  -m                Output multiplication average instead\n"));
    printf(_("  -h, --help        Show this message\n"));
    printf(_("  -v, --version     Show programm version\n"));
}

int main(int argc, char *argv[]) {
    setlocale (LC_ALL, "");
    bindtextdomain (PACKAGE, LOCALE_DIR);
    textdomain (PACKAGE);

    int use_mul = 0;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-m") == 0) {
            use_mul = 1;
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            help();
            return 0;
        }
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            printf(_("Version: %s\n"), VERSION);
            return 0;
        }
    }

    printf(_("Enter amount of numbers you wan't to enter: "));
    int n;
    scanf("%d", &n);

    if (n >= MAX_NUMBERS) {
        printf(_("Error: too many numbers, I don't have enough memory for this\n"));
        return 1;
    }

    int numbers[MAX_NUMBERS];
    printf(_("Enter numbers themselfs:\n"));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &numbers[i]);
    }

    if (use_mul) {
        printf(_("Here is your average mul: %lld\n"), average_mul(n, numbers));
    }
    else {
        printf(_("Here is your average sum: %lld\n"), average_sum(n, numbers));
    }

    return 0;
}
