#include "stringutils.h"
#include "stdio.h"
#include <stdlib.h> 
#define INIT_LEN 10

int getlineImpl(char **line) {
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

void reverse(char str[]) {
    int end = 0;
    while (str[end] != '\n' && str[end] != '\0') {
        end++;
    }

    end--;
    int start = 0;
    while (start < end) {
        char tmp = str[end];
        str[end] = str[start];
        str[start] = tmp;
        start++;
        end--;
    }
}

char isEmpty(int ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}

// 12345 [1, 3]
char* substring(char* line, int startIndex, int endIndex) {
    int stirngLen = endIndex - startIndex;
    
    //stirng len + \0
    char* newLine = malloc(sizeof(char) * (stirngLen + 1));
    for (int i = 0; i < stirngLen; i++) {
        newLine[i] = line[startIndex++];
        if (newLine[i] == '\0') {
            return newLine;
        }
    }
    newLine[stirngLen] = '\0';

    return newLine;
}

char* trim(char* line) {
    int startIndex = -1;
    int endIndex = 0;

    while (line[endIndex] != '\0') {
        if (startIndex != -1) {
            endIndex++;
            continue;
        }

        while (isEmpty(line[endIndex])) {
            endIndex++;
        }

        startIndex = endIndex;
    }
    endIndex--;

    while (endIndex > 0 && isEmpty(line[endIndex])) {
        endIndex--;
    }

    return substring(line, startIndex, endIndex + 1);
}

char isBlank(char* line) {
    int i = 0;
    while (line[i] != '\0') {
        if (!isEmpty(line[i])) {
            return 0;
        }
        i++;
    }

    return 1;
}