#include "../lib/char_utils.h"
#include "../lib/list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define DIGIT 'd'
#define IDENTEFIER 'i'
#define KEYWORD 'k'
#define MAX_TOKEN_LEN 100

typedef struct Token {
  char type;
  char val[MAX_TOKEN_LEN];
  size_t size;
} Token;

char is_single_token(const char);
void handle_declaration(const List *, size_t, size_t);
void handle_direct_declaration(const List *, size_t, size_t);
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
      if (isEmpty(ch)) {
        continue;
      }

      if (is_single_token(ch)) {
        break;
      }

      token[tokenLen++] = ch;
    }

    const Token long_token = to_token(token, tokenLen);
    list_add(tokens, &long_token);
    list_add(tokens, &((Token){.type = ch}));
  }

  return tokens;
}

char is_single_token(const char ch) {
  return ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '*';
}

char is_keyword(const char *word) {
  return isEquals(word, "void") || isEquals(word, "int") ||
         isEquals(word, "char") || isEquals(word, "double") ||
         isEquals(word, "float") || isEquals(word, "const");
}

Token to_token(const char *value, const size_t len) {
  Token token = {.size = len};
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

void handle_direct_declaration(const List *tokens, size_t start_index,
                               size_t finish_index) {
  Token curr_token;
  list_get_by_index(tokens, start_index, &curr_token);

  if (curr_token.type == '(') {
    int toClose = 1;

    size_t to = start_index + 1;
    while (toClose != 0) {
      list_get_by_index(tokens, to++, &curr_token);

      if (curr_token.type == '(') {
        toClose++;
      }

      if (curr_token.type == ')') {
        toClose--;
      }
    }

    handle_declaration(tokens, start_index + 1, to - 1);
    start_index = to;
  } else if (curr_token.type == IDENTEFIER) {
    printf("%s: ", curr_token.val);
    start_index++;
  }

  if (start_index >= finish_index) {
    return;
  }

  list_get_by_index(tokens, start_index++, &curr_token);
  // function call
  if (curr_token.type == '(') {
    printf("function returning ");
  }

  // arr
  if (curr_token.type == '[') {
    if (start_index != finish_index - 1) {
      list_get_by_index(tokens, start_index, &curr_token);
      printf("array [%s] of ", curr_token.val);
    } else {
      printf("array of ");
    }
  }
}

void handle_declaration(const List *tokens, const size_t start_index,
                        const size_t finish_index) {
  Token token;
  list_get_by_index(tokens, start_index, &token);

  if (token.type == '*') {
    handle_direct_declaration(tokens, start_index + 1, finish_index);
    printf("pointer to ");
  } else {
    handle_direct_declaration(tokens, start_index, finish_index);
  }
}

int main() {
  List *tokens = read_tokens();

  int keyWordCount = 0;
  while (1) {
    Token token;
    list_get_by_index(tokens, keyWordCount, &token);

    if (token.type != KEYWORD) {
      break;
    }
    keyWordCount++;
  }

  handle_declaration(tokens, keyWordCount, list_size(tokens));

  for (int i = 0; i < keyWordCount; i++) {
    Token token;
    list_get_by_index(tokens, i, &token);

    printf("%s ", token.val);
  }
  printf("\n");

  list_destroy(tokens);

  return 0;
}
