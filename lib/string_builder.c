#include "string_builder.h"
#include "stdlib.h"
#include "stdio.h"

#define INIT_CAPACITY 2
#define EXPAND_COEF 1.5

struct StringBuilder createStringBuilder() {
    struct StringBuilder builder = {
        .string = (char*) malloc(sizeof(char) * INIT_CAPACITY),
        .capacity = INIT_CAPACITY,
        .length = 0
    };
    
    return builder;
}

void destroyStringBuilder(struct StringBuilder builder) {
    free(builder.string);
}

void append(struct StringBuilder* builder, struct String string) {
    if (builder->capacity <= builder->length + string.length) {
        while (builder->capacity <= builder->length + string.length) {
            builder->capacity = (int) (builder->capacity * EXPAND_COEF);
        }

        char* prevString =  builder->string;
        builder->string = (char*) malloc(sizeof(char) * builder->capacity);
        for (int i = 0; i < builder->length; i++) {
            builder->string[i] = prevString[i];
        }
        builder->string[builder->length] = '\0';      

        free(prevString);
    }

    for (int i = 0; i < string.length; i++) {
        builder->string[builder->length++] = string.str[i];
    }
    builder->string[builder->length] = '\0';
}

struct String stringBuilderToString(struct StringBuilder builder) {
    return createString(builder.string);
}