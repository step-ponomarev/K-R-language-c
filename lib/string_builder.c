#include "string_builder.h"
#include "stdio.h"
#include "stdlib.h"

#define INIT_CAPACITY 2
#define EXPAND_COEF 1.5

StringBuilder createStringBuilder() {
  return (
      (StringBuilder){.string = (char *)malloc(sizeof(char) * INIT_CAPACITY),
                      .capacity = INIT_CAPACITY,
                      .length = 0});
}

void destroyStringBuilder(StringBuilder builder) { free(builder.string); }

void append(StringBuilder *builder, String string) {
  if (builder->capacity <= builder->length + string.length) {
    while (builder->capacity <= builder->length + string.length) {
      builder->capacity = (int)(builder->capacity * EXPAND_COEF);
    }

    char *prevString = builder->string;
    builder->string = (char *)malloc(sizeof(char) * builder->capacity);
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

String stringBuilderToString(StringBuilder builder) {
  return createString(builder.string);
}
