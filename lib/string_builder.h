#ifndef STRING_BUILDER_H_
#define STRING_BUILDER_H_

#include "string.h"
struct StringBuilder {
    struct String** strings;
    int capacity;
    int count;
    int length;
    void* ref;
};

struct StringBuilder* createStringBuilder();
void destroyStringBuilder(struct StringBuilder* builder);

struct StringBuilder* append(struct StringBuilder* builder, struct String* string);
struct String* stringBuilderToString(struct StringBuilder* builder);

#endif