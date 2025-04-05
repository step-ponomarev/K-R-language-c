#include "stdio.h"

#define GYSTO_SYMBOL 182
#define MAX_WORD_LEN 100

#define WORD_START 1
#define WORD_END 0

char isSymbol(int ch);

int main() {
    int wordLength[MAX_WORD_LEN];
    for (int i = 0; i < MAX_WORD_LEN; i++) {
        wordLength[i] = 0;
    }

    int state = WORD_END;

    int ch;
    int len = 0;
    while ((ch = getchar()) != EOF) {
        if (isSymbol(ch)) {
            state = WORD_START;
            len++;
        } else {
            if (state == WORD_START) {
                wordLength[len]++;
                len = 0;
                state = WORD_END;
            }
        }
    }

    for (int i = 0; i < MAX_WORD_LEN; i++) {
        if (wordLength[i] <= 0) {
            continue;
        }

        printf("%3d: %0*d\n", i, wordLength[i], 0);
    }

    return 0;
}

char isSymbol(int ch) {
    return ch > 32;
}