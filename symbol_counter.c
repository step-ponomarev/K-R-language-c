#include "stdio.h"

#define SYMBOL_COUNT 256 - 33

char isEmpty(int ch);

int main() {
    int symbols[SYMBOL_COUNT];
    for (int i = 0; i < SYMBOL_COUNT; i++) {
        symbols[i] = 0;
    }

    int ec = 0;
    int ch;
    
    while ((ch = getchar()) != EOF) {
        if (isEmpty(ch)) {
            ec++;
            continue;
        }

        if (ch <= 32) {
            continue;
        }

        symbols[ch - 33]++;
    }

    for (int i = 0; i < SYMBOL_COUNT; i++) {
        if (symbols[i] != 0) {
            printf("%c : %3d\n", i + 33 , symbols[i]);
        }
    }

    printf("Empty symbols : %3d\n", ec);

    return 0;
}

char isEmpty(int ch) {
    return ch == '\n' || ch == ' ' || ch == '\t';
}