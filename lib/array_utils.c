#include "array_utils.h"
#include "stdlib.h"

void expand(char** str, int oldLen, int newLen) {
    char * newStr = malloc(sizeof(char) * newLen);

    int minLen;
    if (oldLen < newLen) {
        minLen = oldLen;
    } else {
        minLen = newLen;
    }

    for (int i = 0; i < minLen; i++) {
        newStr[i] = *str[i];
    }

    free(*str);
    *str = newStr;
}