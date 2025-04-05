#include "stdio.h"

#define IN  1
#define OUT 0

char isSpace(int ch);

int main() {
    int lc, wc, sc;
    lc = wc = sc = 0;

    char state = OUT;

    int ch;
    while ((ch = getchar()) != EOF) {
        sc++;

        if (ch == '\n') {
            lc++;
            state = OUT;
        } else if (isSpace(ch)) {
            state = OUT;
        } else {
            if (state == OUT) {
                state = IN;
                wc++;
            }
        }
    }

    printf("Line Count: %3d | Word Count: %3d | Symbol Count: %3d", lc, wc, sc);

    return 0;
}

char isSpace(int ch) {
    return ch == ' ' || ch == '\t';
}
