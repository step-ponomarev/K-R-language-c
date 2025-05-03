#include "../compiler/tokenizer.h"
#include <stddef.h>
#include <stdio.h>

void handle_declaration(const List *, size_t, size_t);
void handle_direct_declaration(const List *, size_t, size_t);
void handle_method_args(const List *, size_t, size_t);

int main() {
  List *tokens = read_tokens();
  const size_t token_count = list_size(tokens);

  int keyWordCount = 0;
  Token token;
  do {
    list_get_by_index(tokens, keyWordCount, &token);
  } while (token.type == KEYWORD && (++keyWordCount < token_count));

  handle_declaration(tokens, keyWordCount, token_count);

  for (int i = 0; i < keyWordCount; i++) {
    list_get_by_index(tokens, i, &token);

    printf("%s ", token.val);
  }
  printf("\n");

  list_destroy(tokens);

  return 0;
}

int get_close_index(const List *tokens, const size_t from, const size_t to) {
  Token curr_token;
  list_get_by_index(tokens, from, &curr_token);

  const char open_symbol = curr_token.type;
  const char close_symbol = open_symbol == '(' ? ')' : ']';

  int toClose = 1;
  size_t i = from + 1;
  while (toClose != 0 && i < to) {
    list_get_by_index(tokens, i++, &curr_token);

    if (curr_token.type == open_symbol) {
      toClose++;
    }

    if (curr_token.type == close_symbol) {
      toClose--;
    }
  }

  if (toClose > 0) {
    return -1;
  }

  return i - 1;
}

void handle_direct_declaration(const List *tokens, size_t from, size_t to) {
  if (to <= from) {
    return;
  }

  Token curr_token;
  list_get_by_index(tokens, from, &curr_token);

  if (curr_token.type == '(') {
    const int close_index = get_close_index(tokens, from, to);
    handle_declaration(tokens, from + 1, close_index);
    from = close_index + 1;
  } else if (curr_token.type == IDENTEFIER) {
    printf("%s: ", curr_token.val);
    from++;
  }

  if (from == to) {
    return;
  }

  list_get_by_index(tokens, from++, &curr_token);
  // function call
  if (curr_token.type == '(') {
    const int close_index = get_close_index(tokens, from - 1, to);

    printf("function ");
    if (from != close_index) {
      printf("\b");
      handle_method_args(tokens, from, close_index);
    }
    printf("returning ");
  }

  // arr
  if (curr_token.type == '[') {
    if (from != to - 1) {
      list_get_by_index(tokens, from, &curr_token);
      printf("array[%s] of ", curr_token.val);
    } else {
      printf("array[] of ");
    }
  }
}

void handle_declaration(const List *tokens, const size_t from,
                        const size_t to) {
  if (to <= from) {
    return;
  }

  Token token;
  list_get_by_index(tokens, from, &token);

  if (token.type == '*') {
    handle_direct_declaration(tokens, from + 1, to);
    printf("pointer to ");
  } else {
    handle_direct_declaration(tokens, from, to);
  }
}

void handle_method_args(const List *tokens, size_t from, size_t to) {
  Token curr_token;
  printf("(");

  while (from < to) {
    list_get_by_index(tokens, from++, &curr_token);
    if (curr_token.type == KEYWORD || curr_token.type == IDENTEFIER) {
      printf("%s ", curr_token.val);
    } else {
      printf("\b%c ", curr_token.type);
    }
  }

  printf("\b) ");
}
