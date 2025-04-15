#ifndef STRING_BUILDER_H_
#define STRING_BUILDER_H_

#include "string.h"

typedef struct {
  char *string;
  int capacity;
  int length;
} StringBuilder;

StringBuilder createStringBuilder();
void destroyStringBuilder(StringBuilder builder);

void append(StringBuilder *builder, String string);
String stringBuilderToString(StringBuilder builder);

#endif
