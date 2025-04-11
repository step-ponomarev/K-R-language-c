#include "string_builder.h"
#include "stdlib.h"
#include "stdio.h"

#define INIT_CAPACITY 10
#define EXPAND_COEF 1.5

struct StringBuilder* createStringBuilder() {
    struct StringBuilder* builder = (struct StringBuilder*) malloc(sizeof(struct StringBuilder));
    builder->strings = (struct String**) malloc(sizeof(struct String*) * INIT_CAPACITY);
    builder->capacity = INIT_CAPACITY;
    builder->count = 0;
    builder->length = 0;
    builder->ref = builder;
    
    return builder;
}

void destroyStringBuilder(struct StringBuilder* builder) {
    for (int i = 0; i < builder->count; i++) {
        destroyString(builder->strings[i]);
    }
    free(builder->strings);
    free(builder->ref);
}

struct StringBuilder* append(struct StringBuilder* builder, struct String* string) {
    if (builder->count == builder->capacity) {
        struct String** prevStrings = builder->strings;
        
        builder->capacity = (int) builder->capacity * EXPAND_COEF;
        builder->strings = (struct String**) malloc(sizeof(struct String*) * builder->capacity);
        for (int i = 0; i < builder->count; i++) {
            builder->strings[i] = prevStrings[i];
        }

        free(prevStrings);
    }

    builder->length += string->length;
    builder->strings[builder->count++] = string;

    return builder;
}

struct String* stringBuilderToString(struct StringBuilder* builder) {
    char* str = (char*) malloc(sizeof(char) * (builder->length + 1));
    int p = 0;
    for (int i = 0; i < builder->count; i++) {
        int j = 0;
        while(builder->strings[i]->str[j] != '\0') {
            str[p++] = builder->strings[i]->str[j];
            j++;
        }
    }
    str[p] = '\0';

    return createString(str);
}

int main() {
    struct StringBuilder* builder = createStringBuilder();

    for (int i = 0; i < 3; i++) {
        append(builder, createString("as"));
    }

    printf("%s\n", stringBuilderToString(builder)->str);
    destroyStringBuilder(builder);

    return 0;
}