#include "../lib/iolib.h"
#include "../lib/stack.h"
#include "stdio.h"
#include "stdlib.h"
#include <stdlib.h>

#define OP_TYPE_DIGIT 0b0
#define OP_TYPE_OP 0b1

typedef struct Token {
  int op;
  short int op_type;
} Token;

char isOp(const char ch) {
  return ch == '-' || ch == '+' || ch == '/' || ch == '*' || ch == '%';
}

int calculate(const int a, const int b, const char op) {
  switch (op) {
  case '-':
    return a - b;
  case '+':
    return a + b;
  case '*':
    return a * b;
  case '/':
    return a / b;
  case '%':
    return a % b;
  }

  return -1;
}

int main() {
  char wrd[0];
  int len = 0;

  Stack *stack = createStack(sizeof(Token));
  while ((len = readWord(wrd)) > 0) {
    if (len == 1 && isOp(wrd[0])) {
      Token digit2;
      stackPop(stack, &digit2);

      Token digit1;
      stackPop(stack, &digit1);

      stackAdd(stack, &((Token){.op = calculate(digit1.op, digit2.op, wrd[0]),
                                .op_type = OP_TYPE_DIGIT}));
      continue;
    }

    stackAdd(stack, &((Token){.op = atoi(wrd), .op_type = OP_TYPE_DIGIT}));
  }

  Token res;
  stackPop(stack, &res);

  printf("Result: %d\n", res.op);

  return 0;
}
