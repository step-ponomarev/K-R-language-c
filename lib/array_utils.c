#include "array_utils.h"
#include "stdlib.h"
#include "stdio.h"

void expand(char** str, int oldLen, int newLen) {
    char * newStr = malloc(sizeof(char) * newLen);
    for (int i = 0; i < oldLen; i++) {
        newStr[i] = (*str)[i];
    }

    free(*str);
    *str = newStr;
}