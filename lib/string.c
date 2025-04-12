#include "string.h"
#include "stdlib.h"

char isEmpty(char);

struct String createString(char* ch) {
    int len = 0;
    while (ch[len] != '\0') {
        len++;
    }

    char* str = malloc(sizeof(char) * len);
    for (int i = 0; i <= len; i++) {
        str[i] = ch[i];
    }

    return ((struct String) {
        .str = str,
        .length = len
    });
}

void destroyString(struct String string) {
    free(string.str);
}

struct String substring(struct String string, int from, int to) {
    if (from < 0 || to > string.length || to <= from) {
        struct String errorString = {
            .str = NULL,
            .length = -1
        };

        return errorString;
    }

    int newLen = to - from;
    char * newStr = malloc(sizeof(char) * newLen + 1);
    for (int i = from; i < to; i++) {
        newStr[i - from] = string.str[i];
    }
    newStr[to] = '\0';

    return ((struct String) {
        .str = newStr,
        .length = newLen
    });
}

struct String trim(struct String str) {
    int start = 0;
    int end = str.length - 1;
    while (end >= 0) {
        if (!isEmpty(str.str[end])) {
            break;
        }
    }

    end++;
    if (end == 0) {
        char * emptyString = malloc(sizeof(char));
        emptyString[0] = '\0';

        return ((struct String) {
            .str = emptyString,
            .length = 0
        });;
    }

    while (start < str.length) {
        if (!isEmpty(str.str[start])) {
            break;
        }
        start++;
    }

    return substring(str, start, end);
}

char isEmpty(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}