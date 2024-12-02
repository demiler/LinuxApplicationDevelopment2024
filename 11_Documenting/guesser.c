//
// Created on 2024.02.02.
//

/** @mainpage
 * # Game with ARTIFICIAL INTELEGENT (no)
 *
 * Play with the ARTIFICIAL INTELEGENT that can easily guess your number (in several attempts)
 * ((maybe))
 *
 * Custom MODEL, don't use any OPENAI api's so you don't need to provide it a token
 *
 */

/** @file guesser.c
 * Implementation of the game
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

/**< Array with romanian numbers from 0 to 100 (included). (REALLY FAST IMPLEMENTATION!) **/
const char *ROMANIAN[] = {
    "N",      "I",       "II",     "III",     "IV",       "V",      "VI",
    "VII",    "VIII",    "IX",     "X",       "XI",       "XII",    "XIII",
    "XIV",    "XV",      "XVI",    "XVII",    "XVIII",    "XIX",    "XX",
    "XXI",    "XXII",    "XXIII",  "XXIV",    "XXV",      "XXVI",   "XXVII",
    "XXVIII", "XXIX",    "XXX",    "XXXI",    "XXXII",    "XXXIII", "XXXIV",
    "XXXV",   "XXXVI",   "XXXVII", "XXXVIII", "XXXIX",    "XL",     "XLI",
    "XLII",   "XLIII",   "XLIV",   "XLV",     "XLVI",     "XLVII",  "XLVIII",
    "XLIX",   "L",       "LI",     "LII",     "LIII",     "LIV",    "LV",
    "LVI",    "LVII",    "LVIII",  "LIX",     "LX",       "LXI",    "LXII",
    "LXIII",  "LXIV",    "LXV",    "LXVI",    "LXVII",    "LXVIII", "LXIX",
    "LXX",    "LXXI",    "LXXII",  "LXXIII",  "LXXIV",    "LXXV",   "LXXVI",
    "LXXVII", "LXXVIII", "LXXIX",  "LXXX",    "LXXXI",    "LXXXII", "LXXXIII",
    "LXXXIV", "LXXXV",   "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC",
    "XCI",    "XCII",    "XCIII",  "XCIV",    "XCV",      "XCVI",   "XCVII",
    "XCVIII", "XCIX",    "C"
};
/**< dirty hack to find length of a constant array **/
const unsigned int N_ROMANIAN = sizeof(ROMANIAN) / sizeof(void*);

/** Convert integer to romanian number (in string)
  *
  * @param num Integer that needs to be converted to romanian string
  * @returns string Non NULL pointer to a null-terminated string if success, NULL otherwise
  */
const char* const to_romanian(unsigned int num) {
    if (num >= N_ROMANIAN) {
        return NULL;
    }
    return ROMANIAN[num];
}

/** Convert romanian number from string to integer
  *
  * @param romnum Romanian number in string that needs to be converted back to integer
  * @returns int Postive value if conversion successfull, -2 if NULL was provided, -1 if failed
  */
int from_romanian(const char* const romnum) {
    if (romnum == NULL) {
        return -2;
    }

    for (unsigned int i = 0; i < N_ROMANIAN; ++i) {
        if (strcmp(romnum, ROMANIAN[i]) == 0) {
            return i;
        }
    }
    return -1;
}

/** Prints help message
  *
  */
void printhelp() {
    printf(_("Usage: guesser [-r|-h]\n"));
    printf(_("Play a game with the computer where it should guess your number!\n\n"));
    printf(_("  -r         Use romanian numbers instead of arabic\n"));
    printf(_("  -h|--help  Show this message\n"));
}

int main(int argc, char* argv[]) {
    setlocale (LC_ALL, "");
#if defined PACKAGE && defined LOCALE_DIR  //provided at compile time
    bindtextdomain (PACKAGE, LOCALE_DIR);
    textdomain (PACKAGE);
#endif

    unsigned int use_romanian = 0;
    if (argc > 2) {
        printf(_("Error: too many arguments\n\n"));
        printhelp();
        return -1;
    }
    if (argc == 2) {
        if (strcmp(argv[1], "-r") == 0) {
            use_romanian = 1;
        }
        else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            printhelp();
            return 0;
        }
        else {
            printf(_("Error: unknown argument '%s'\n"), argv[1]);
            return -2;
        }
    }

    int low = 1, high = 100;
    if (use_romanian) {
        printf(_("Guess a number between %s and %s\n"), to_romanian(low), to_romanian(high));
    }
    else {
        printf(_("Guess a number between %d and %d\n"), low, high);
    }
    printf(_("...press any to continue...\n"));
    getchar();

    char didIGuess = 'l';
    int number;
    while (didIGuess != 'e') {
        int prevNumber = number;
        number = (high + low) / 2;

        if (prevNumber == number) {
            if (use_romanian) {
                printf(_("You are lying, it has to be %s!\nI'm not playing w/ you >:(\n"),
                        to_romanian(number)
                );
            }
            else {
                printf(_("You are lying, it has to be %d!\nI'm not playing w/ you >:(\n"), number);
            }
            exit(1);
        }

        if (use_romanian) {
            printf(_("Is it %s? [l/e/g] "), to_romanian(number));
        }
        else {
            printf(_("Is it %d? [l/e/g] "), number);
        }
        scanf("%c", &didIGuess);

        while (didIGuess != 'l' && didIGuess != 'e' && didIGuess != 'g') {
            if (didIGuess != '\n') {
                printf("[y/n] ");
            }
            scanf("%c", &didIGuess);
        }

        if (didIGuess == 'l') {
            high = number;
        }
        else {
            low = number;
        }
    }

    if (use_romanian) {
        printf(_("I knew it was %s!\n"), to_romanian(number));
    }
    else {
        printf(_("I knew it was %d!\n"), number);
    }

    return 0;
}
