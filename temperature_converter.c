#include "stdio.h"

int convert(int farth) {
    return 5 * (farth - 32) / 9;
}

int main() {
    int farth, celsium;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    while (lower < upper) {
        farth = lower;
        celsium = convert(farth);
        printf("%d\t%d\n", farth, celsium);
        lower += step;
    }

    return 0;
}

