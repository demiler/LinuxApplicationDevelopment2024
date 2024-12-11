#include "calc.h"

long long int average_sum(int n, int *numbers) {
    long long int avg = 0;
    for (int i = 0; i < n; ++i) {
        avg += numbers[i];
    }
    avg /= n;
    return avg;
}

long long int average_mul(int n, int *numbers) {
    long long int avg = 1;
    for (int i = 0; i < n; ++i) {
        if (numbers[i] == 0) return 0;
        avg *= numbers[i];
    }
    avg /= n;
    return avg;
}

