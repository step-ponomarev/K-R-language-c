#include "../lib/char_utils.h"
#include "../lib/hash_map.h"
#include "../lib/iolib.h"
#include "../lib/stack.h"
#include "map.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define TYPE_DIGIT 0
#define TYPE_OP 1
#define TYPE_VARIABLE 2

typedef enum TokenType {
  DIGIT,
  UNARY_OPERATOR,
  BINARY_OPERATOR,
  VAR_DIFINITION,
  VARIABLE,
  PRINT
} TokenType;

typedef struct Token {
  void *value;
  TokenType type;
  size_t size;
} Token;

int get_val(const Map *, const Token);
char *get_var_name();
char is_unary_operator(const char[]);
char is_binary_operator(const char[]);
char is_number(const char[]);
Token parse_token(const char[], const size_t);
Token token_create(const void *, const size_t, const TokenType);
int binary_op(const int, const int, const char[]);
int unary_op(const char[], const int);

int main() {
  char wrd[0];
  int len = 0;

  Stack *stack = create_stack(sizeof(Token));
  Map *map = map_create();
  while ((len = readWord(wrd)) > 0) {
    Token token = parse_token(wrd, len);
    if (token.type == DIGIT || token.type == VARIABLE) {
      stack_add(stack, &token);
      continue;
    }

    Token secondOperand;
    stack_pop(stack, &secondOperand);

    if (token.type == PRINT) {
      const int val = get_val(map, secondOperand);
      printf("%s = %d\n", secondOperand.value, val);
      free(secondOperand.value);

      continue;
    }

    if (token.type == UNARY_OPERATOR) {
      int val = get_val(map, secondOperand);
      int res = unary_op(token.value, val);

      const Token token = token_create(&res, sizeof(int), DIGIT);
      stack_add(stack, &token);

      continue;
    }

    Token firstOperand;
    stack_pop(stack, &firstOperand);

    if (token.type == VAR_DIFINITION) {
      const MapEntry key = {.val = firstOperand.value,
                            .size = firstOperand.size};

      int *val = malloc(sizeof(int));
      memcpy(val, secondOperand.value, secondOperand.size);

      const MapEntry value = {.val = val, .size = secondOperand.size};
      map_put(map, key, value);
      free(val);

      continue;
    }

    const int res = binary_op(get_val(map, firstOperand),
                              get_val(map, secondOperand), token.value);

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

  map_destroy(map);
  destroy_stack(stack);

  return 0;
}

Token parse_token(const char str[], const size_t len) {
  if (is_number(str)) {
    const int res = atoi(str);
    return token_create(&res, sizeof(int), DIGIT);
  }

  if (is_binary_operator(str)) {
    return token_create(str, len + 1, BINARY_OPERATOR);
  }

  if (is_unary_operator(str)) {
    return token_create(str, len + 1, UNARY_OPERATOR);
  }

  if (isEquals("define", str)) {
    return token_create("", 0, VAR_DIFINITION);
  }

  if (isEquals("print", str)) {
    return token_create("", 0, PRINT);
  }

  char *var = malloc(sizeof(char) * (len + 1));
  memcpy(var, str, len + 1);

  return token_create(var, len + 1, VARIABLE);
}

Token token_create(const void *data, const size_t size, const TokenType type) {
  void *dataCopy = malloc(size);
  memcpy(dataCopy, data, size);

  return (Token){.value = dataCopy, .size = size, .type = type};
}

int get_val(const Map *map, const Token token) {
  int res;
  if (token.type == DIGIT) {
    memcpy(&res, token.value, token.size);
  }

  if (token.type == VARIABLE) {
    char varname[token.size];
    memcpy(varname, token.value, token.size);

    map_get(map, (MapEntry){.val = varname, .size = token.size}, &res);
  }

  return res;
}

char is_binary_operator(const char wrd[]) {
  if (wrd[1] != '\0') {
    return isEquals("pow", wrd);
  }

  const char ch = wrd[0];

  return ch == '-' || ch == '+' || ch == '/' || ch == '*' || ch == '%';
}

char is_unary_operator(const char wrd[]) {
  return isEquals("exp", wrd) || isEquals("sin", wrd);
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

  if (isEquals("pow", op)) {
    return pow(a, b);
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

int unary_op(const char fn[], const int a) {
  if (isEquals("exp", fn)) {
    return exp(a);
  }

  if (isEquals("sin", fn)) {
    return sin(a);
  }

  return -1;
}
