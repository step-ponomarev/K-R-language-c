#include "string.h"
#include "stdlib.h"

struct String* toString(char * ch) {
    int len = 0;
    while (ch[len] != '\0') {
        len++;
    }

    char* str = malloc(sizeof(char) * len);
    for (int i = 0; i <= len; i++) {
        str[i] = ch[i];
    }

    struct String* string = (struct String*) malloc(sizeof(struct String));
    string->str = str;
    string->len = len;
    string->ref = string;

    return string;
}

void destroy(struct String* string) {
    free(string->str);
    free(string->ref);
}