#include "iolib.h"
#include "stdio.h"
#include "stdlib.h"
#include "array_utils.h"
#include "char_utils.h"

#define INIT_LINE_LEN 100
#define INIT_WORD_LEN 10
#define EXPAND_COEF 2

struct String readline() {
    int currLen = INIT_LINE_LEN;
    char * chArr = malloc(sizeof(char) * currLen + 1);
    int i = 0;
    
    int ch;
    while (((ch = getchar()) != EOF) && (ch != '\n')) {
        if (i == currLen - 1) {
            int newLen = (int) (currLen * EXPAND_COEF);
            expand(&chArr, currLen, newLen);
            currLen = newLen;
        }
    
        chArr[i++] = ch;
    }
    chArr[i] = '\0';

    struct String res = createString(chArr);
    free(chArr);

    return res;
}

struct String readWord() {
    int currLen = INIT_WORD_LEN;

    // skip start empty
    int ch;
    while ((ch = getchar()) != EOF && (isEmpty(ch))) {}

    if (ch == EOF) {
        return ((struct String) {
            .str = NULL,
            .length = 0
        });
    }

    char * chArr = malloc(sizeof(char) * currLen + 1);
    chArr[0] = ch;
    int i = 1;
    
    while ((ch = getchar()) != EOF) {
        if (i == currLen - 1) {
            int newLen = (int) (currLen * EXPAND_COEF);
            expand(&chArr, currLen, newLen);
            currLen = newLen;
        }

        if (isEmpty(ch)) {
            break;
        }
    
        chArr[i++] = ch;
    }
    chArr[i] = '\0';

    struct String res = createString(chArr);
    free(chArr);

    return res;
}