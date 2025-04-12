#include "iolib.h"
#include "stdio.h"
#include "stdlib.h"
#include "array_utils.h"

#define INIT_LEN 1
#define EXPAND_COEF 2

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