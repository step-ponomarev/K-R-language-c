#include "stdio.h"

int main() {
    int c;
    long spaceCount = 0;
    long tabCount = 0;
    long endOfLineCount = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            spaceCount++;
        }

        if (c == '\t') {
            tabCount++;
        }

        if (c == '\n') {
            endOfLineCount++;
        }
    }

    printf("Space count: %3ld\nTabCount: %3ld\nEndOfLineCount: %3ld\n", spaceCount, tabCount, endOfLineCount);

    return 0;
}