#include "iolib.h"
#include "stdio.h"
#include "stdlib.h"

#define INIT_LEN 1
#define EXPAND_COEF 2

void expand(char**, int oldLen, int newLen);

struct String readline() {
    int currLen = INIT_LEN;
    char * chArr = malloc(sizeof(char) * currLen + 1);
    int i = 0;
    
    int ch;
    while (((ch = getchar()) != EOF) && (ch != '\n')) {
        if (i == currLen - 1) {
            int newLen = (int) currLen * EXPAND_COEF;
            expand(&chArr, currLen, newLen);
        }
    
        chArr[i++] = ch;
    }
    chArr[i] = '\0';

    struct String res = createString(chArr);
    free(chArr);

    return res;
}

void expand(char** str, int oldLen, int newLen) {
    char * newStr = malloc(sizeof(char) * newLen);
    for (int i = 0; i < oldLen; i++) {
        newStr[i] = *str[i];
    }

    free(*str);
    *str = newStr;
}