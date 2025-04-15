#ifndef _COMPILER_TOOLS_H_
#define _COMPILER_TOOLS_H_

#include "../../lib/string.h"

enum token_type {
  KEYWORD,
  IDENTIFIER,
  CONSTANT,
  STRING,
  OPERATOR,
  SPECIAL_SYMBOL
};

typedef struct {
  String name;
  token_type type;
} Token;

Token readToken();

#endif
