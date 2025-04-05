#include "stdio.h"

#define WORD_FOUND  1
#define WORD_NOT_FOUND 0

char isSymbol(int ch);

int main() {
    char state = WORD_NOT_FOUND;
    
    int ch;
    while ((ch = getchar()) != EOF) {
        if (isSymbol(ch)) {
            state = WORD_FOUND;
            putchar(ch);
        } else {
            if (state != WORD_NOT_FOUND) {
                state = WORD_NOT_FOUND;
                putchar('\n');
            }
        }
    }

    return 0;
}

char isSymbol(int ch) {
    return ch > 32;
}