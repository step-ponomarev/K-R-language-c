#include "../lib/char_utils.h"
#include "../lib/stack.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define TYPE_DIGIT 0
#define TYPE_OP 1
#define TYPE_VARIABLE 2

typedef enum TokenType { DIGIT, BINARY_OPERATOR } TokenType;

typedef struct Token {
  void *value;
  TokenType type;
  size_t size;
} Token;

int get_val(const Token);
char *get_var_name();
char is_unary_operator(const char[]);
char is_binary_operator(const char[]);
char is_number(const char[]);
Token parse_token(const char[], const size_t);
Token token_create(const void *, const size_t, const TokenType);
int binary_op(const int, const int, const char[]);

int main(int argc, char *argv[]) {
  char *wrd;
  int len = 0;

  Stack *stack = create_stack(sizeof(Token));
  for (int i = 1; i < argc; i++) {
    len = copy_string(argv[i], &wrd);

    Token token = parse_token(wrd, len);
    if (token.type == DIGIT) {
      stack_add(stack, &token);
      continue;
    }

    Token secondOperand;
    stack_pop(stack, &secondOperand);

    Token firstOperand;
    stack_pop(stack, &firstOperand);
    const int res =
        binary_op(get_val(firstOperand), get_val(secondOperand), token.value);

    free(firstOperand.value);
    free(secondOperand.value);

    token = token_create(&res, sizeof(int), DIGIT);
    stack_add(stack, &token);
  }

  Token res;
  stack_pop(stack, &res);

  int resVal;
  memcpy(&resVal, res.value, sizeof(int));
  printf("Result: %d\n", resVal);

  destroy_stack(stack);

  return 0;
}

Token parse_token(const char str[], const size_t len) {
  if (is_binary_operator(str)) {
    return token_create(str, len + 1, BINARY_OPERATOR);
  }

  const int res = atoi(str);
  return token_create(&res, sizeof(int), DIGIT);
}

Token token_create(const void *data, const size_t size, const TokenType type) {
  void *dataCopy = malloc(size);
  memcpy(dataCopy, data, size);

  return (Token){.value = dataCopy, .size = size, .type = type};
}

int get_val(const Token token) {
  int res;
  memcpy(&res, token.value, token.size);

  return res;
}

char is_binary_operator(const char wrd[]) {
  const char ch = wrd[0];

  return ch == '-' || ch == '+' || ch == '/' || ch == '*' || ch == '%';
}

int binary_op(const int a, const int b, const char op[]) {
  if (isEquals("-", op)) {
    return a - b;
  }

  if (isEquals("+", op)) {
    return a + b;
  }

  if (isEquals("*", op)) {
    return a * b;
  }

  if (isEquals("/", op)) {
    return a / b;
  }

  if (isEquals("%", op)) {
    return a % b;
  }

  return -1;
}

char is_number(const char wrd[]) {
  for (int i = 0; wrd[i] != '\0'; i++) {
    if (!isDigit(wrd[i])) {
      return 0;
    }
  }

  return 1;
}
