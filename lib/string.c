#include "string.h"
#include "stdlib.h"

struct String createString(char * ch) {
    int len = 0;
    while (ch[len] != '\0') {
        len++;
    }

    char* str = malloc(sizeof(char) * len);
    for (int i = 0; i <= len; i++) {
        str[i] = ch[i];
    }

    struct String string = {
        str,
        len
    };

    return string;
}

void destroyString(struct String string) {
    free(string.str);
}