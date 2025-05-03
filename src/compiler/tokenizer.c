#include "tokenizer.h"
#include "../lib/char_utils.h"
#include "stdio.h"

char is_single_token(const char);
char is_keyword(const char *);

Token to_token(const char *, const size_t);

List *read_tokens() {
  List *tokens = list_create(sizeof(Token));

  int ch;
  while ((ch = getchar()) != EOF) {
    if (isEmpty(ch)) {
      continue;
    }

    if (is_single_token(ch)) {
      list_add(tokens, &((Token){.type = ch}));
      continue;
    }

    int tokenLen = 0;
    char token[MAX_TOKEN_LEN];
    token[tokenLen++] = ch;

    while ((ch = getchar()) != EOF && tokenLen < MAX_TOKEN_LEN) {
      if (isEmpty(ch) || is_single_token(ch)) {
        break;
      }

      token[tokenLen++] = ch;
    }

    const Token long_token = to_token(token, tokenLen);
    list_add(tokens, &long_token);

    if (!isEmpty(ch)) {
      list_add(tokens, &((Token){.type = ch}));
    }
  }

  return tokens;
}

char is_single_token(const char ch) {
  return ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '*' ||
         ch == ',';
}

char is_keyword(const char *word) {
  return isEquals(word, "void") || isEquals(word, "int") ||
         isEquals(word, "char") || isEquals(word, "double") ||
         isEquals(word, "float") || isEquals(word, "const");
}

Token to_token(const char *value, const size_t len) {
  Token token;
  for (int i = 0; i < len; i++) {
    token.val[i] = value[i];
  }
  token.val[len] = '\0';

  if (isDigit(value[0])) {
    token.type = DIGIT;
  } else {
    token.type = is_keyword(token.val) ? KEYWORD : IDENTEFIER;
  }

  return token;
}
