#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include "../lib/list.h"
#include <stddef.h>

#define MAX_TOKEN_LEN 100

typedef enum TokenType {
  DIGIT = 'd',
  IDENTEFIER = 'i',
  KEYWORD = 'k'
} TokenType;

typedef struct Token {
  char val[MAX_TOKEN_LEN];
  TokenType type;
} Token;

List *read_tokens();

#endif
