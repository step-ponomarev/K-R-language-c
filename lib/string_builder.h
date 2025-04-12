#ifndef STRING_BUILDER_H_
#define STRING_BUILDER_H_

#include "string.h"

struct StringBuilder {
    char* string;
    int capacity;
    int length;
};

struct StringBuilder createStringBuilder();
void destroyStringBuilder(struct StringBuilder builder);

void append(struct StringBuilder* builder, struct String string);
struct String stringBuilderToString(struct StringBuilder builder);

#endif