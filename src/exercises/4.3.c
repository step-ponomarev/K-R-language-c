#include "../lib/char_utils.h"
#include "../lib/iolib.h"
#include "../lib/stack.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include <stdlib.h>

#define OP_TYPE_DIGIT 0b0
#define OP_TYPE_OP 0b1

typedef struct Token {
  int op;
  short int op_type;
} Token;

char isTwoAgrumentsOp(const char *wrd) {
  if (wrd[1] != '\0') {
    return isEquals("pow", wrd);
  }

  const char ch = wrd[0];

  return ch == '-' || ch == '+' || ch == '/' || ch == '*' || ch == '%';
}

char isSingleArgumentOp(const char *wrd) {
  return isEquals("exp", wrd) || isEquals("sin", wrd);
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
  case 'p':
    return pow(a, b);
  }

  return -1;
}

int executeFn(const char fn[], int a) {
  if (isEquals("exp", fn)) {
    return exp(a);
  }

  if (isEquals("sin", fn)) {
    return sin(a);
  }

  return -1;
}

int main() {
  char wrd[0];
  int len = 0;

  Stack *stack = create_stack(sizeof(Token));
  while ((len = readWord(wrd)) > 0) {
    if (isTwoAgrumentsOp(wrd)) {
      Token digit2;
      stack_pop(stack, &digit2);

      Token digit1;
      stack_pop(stack, &digit1);

      stack_add(stack, &((Token){.op = calculate(digit1.op, digit2.op, wrd[0]),
                                 .op_type = OP_TYPE_DIGIT}));
      continue;
    }

    if (isSingleArgumentOp(wrd)) {
      Token digit;
      stack_pop(stack, &digit);

      stack_add(stack, &((Token){.op = executeFn(wrd, digit.op),
                                 .op_type = OP_TYPE_DIGIT}));

      continue;
    }

    stack_add(stack, &((Token){.op = atoi(wrd), .op_type = OP_TYPE_DIGIT}));
  }

  Token res;
  stack_pop(stack, &res);

  printf("Result: %d\n", res.op);

  return 0;
}
