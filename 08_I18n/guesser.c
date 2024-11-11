#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

int main() {
    setlocale (LC_ALL, "");
#if defined PACKAGE && defined LOCALE_DIR  //provided at compile time
    bindtextdomain (PACKAGE, LOCALE_DIR);
    textdomain (PACKAGE);
#endif

    int low = 1, high = 100;
    printf(_("Guess a number between %d and %d\n"), low, high);
    printf(_("...press any to continue...\n"));
    getchar();

    char didIGuess = 'l';
    int number;
    while (didIGuess != 'e') {
        int prevNumber = number;
        number = (high + low - 1) / 2;

        if (prevNumber == number) {
            printf(_("You are lying, it has to be %d!\nI'm not playing w/ you >:(\n"), number);
            exit(1);
        }

        printf(_("Is it %d? [l/e/g] "), number);
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

    printf(_("I knew it was %d!\n"), number);

    return 0;
}
