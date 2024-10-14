#include <stdio.h>


int main(int argc, char *argv[]) {
    if (argc <= 1 || argc > 4) {
        printf("Usage: %s [from=0] to [step=1]\n", argv[0]);
        return 0;
    }

    long long from = 0;
    long long to = 0;
    long long step = 1;

    if (argc == 2) {
        sscanf(argv[1], "%lld", &to);
    }
    else if (argc >= 3) {
        sscanf(argv[1], "%lld", &from);
        sscanf(argv[2], "%lld", &to);
    }
    if (argc == 4) {
        sscanf(argv[3], "%lld", &step);
    }

    //printf("%lld, %lld, %lld\n", from, to, step);
    for (long long i = from; i < to; i += step) {
        printf("%lld\n", i);
    }

    return 0;
}
