#include "stdio.h"
#include <stdlib.h> 

#define INIT_LEN 10

void copy(char from[], char to[]);
void copyWithSize(char from[], char to[], int size);
int getlineImpl(char ** line);

int main() {
    char *currLine = NULL;
    int currLen;

    int maxLen;
    char *maxLine = NULL;
    

    while((currLen = getlineImpl(&currLine)) > 0) {
        if (currLen > maxLen) {
            free(maxLine);
            maxLine = currLine;
            maxLen = currLen;
            currLine = NULL;
        }
    }

    if (maxLine != NULL) {
        printf("%s", maxLine);
    }

    return 0;
}

int getlineImpl(char ** line) {
    int maxLen = INIT_LEN;
    char * chArr = malloc(sizeof(char) * maxLen);
    int i = 0;

    int ch;
    while (((ch = getchar()) != EOF) && (ch != '\n')) {
        if (i == maxLen - 2) {
            maxLen += maxLen;
            char * tmp = malloc(sizeof(char) * maxLen);
            copyWithSize(chArr, tmp, i);
            free(chArr);
            chArr = tmp;
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

void copyWithSize(char from[], char to[], int size) {
    for (int i = 0; i < size; i++) {
        to[i] = from[i];
    }
}

void copy(char from[], char to[]) {
    int i = 0;
    while((to[i] = from[i]) != '\0') {
        i++;
    }
}