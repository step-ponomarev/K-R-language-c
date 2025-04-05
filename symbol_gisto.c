#include "stdio.h"

#define SYMOL_LEN 255

char isSymbol(int ch);

int main() {
    int charCount[SYMOL_LEN];
    for (int i = 0; i < SYMOL_LEN; i++) {
        charCount[i] = 0;
    }

    int ch;
    while ((ch = getchar()) != EOF) {
        if (!isSymbol(ch)) {
            continue;
        }

        charCount[ch - 33]++;
    }

    for (int i = 0; i < SYMOL_LEN; i++) {
        if (charCount[i] <= 0) {
            continue;
        }

        printf("%c: %0*d\n", i + 33, charCount[i], 0);
    }

    return 0;
}

char isSymbol(int ch) {
    return ch > 32;
}