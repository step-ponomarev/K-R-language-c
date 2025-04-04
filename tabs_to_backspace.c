#include "stdio.h"

int main() {
    int c;
    int tmp;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            putchar('\b');
            continue;
        }

        if (c != '/') {
            putchar(c);
            continue;
        }

        tmp = c;
        c = getchar();
        if (c == EOF) {
            putchar(tmp);
            return 0;
        }

        if (c == '/') {
            putchar('\\');
            putchar('\\');
        } else {
            putchar(tmp);
            putchar(c);
        }
    }

    return 0;
}