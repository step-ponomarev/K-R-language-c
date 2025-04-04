#include "stdio.h"

char isEmptySymbol(int ch);

int main() {
    int c;

    while ((c = getchar()) != EOF) {
        if (isEmptySymbol(c)) {
            putchar(' ');
            while (isEmptySymbol((c = getchar()))) {
                if (c == EOF) {
                    return 0;
                }
            }
        }
        
        putchar(c);
    }

    return 0;
}

char isEmptySymbol(int ch) {
    return ch == ' ' || ch == '\t';
}