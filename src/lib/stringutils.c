#include "stringutils.h"
#include "stdio.h"
#include <stdlib.h> 
#define INIT_LEN 10

int readline(char **line) {
    int maxLen = INIT_LEN;
    char * chArr = malloc(sizeof(char) * maxLen);
    int i = 0;

    int ch;
    while (((ch = getchar()) != EOF) && (ch != '\n')) {
        if (i == maxLen - 2) {
            maxLen += maxLen;
            expandArray(&chArr, i, maxLen);
        }

        chArr[i++] = ch;
    }

    if (ch == '\n') {
        chArr[i++] = ch;
    }

    chArr[i] = '\0';

    *line = chArr;

    return i;
}

void expandArray(char **arr, int currSize, int newSize) {
    char * tmp = malloc(newSize);
    copyWithSize(*arr, tmp, currSize);
    free(*arr);
    *arr = tmp;
}

void copyWithSize(char *from, char to[], int size) {
    for (int i = 0; i < size; i++) {
        to[i] = from[i];
    }
}

char isSymbol(int ch) {
    return ch > 32;
}

char isEmpty(int ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}
