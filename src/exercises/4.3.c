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

int main() {
  char wrd[0];
  int len = 0;

  Stack *stack = createStack(sizeof(Token));
  while ((len = readWord(wrd)) > 0) {
    if (len == 1 && isOp(wrd[0])) {
      const Token op = {.op = wrd[0], .op_type = OP_TYPE_OP};
      stackAdd(stack, &op);

      continue;
    }

    const Token digit = {.op = atoi(wrd), .op_type = OP_TYPE_DIGIT};
    stackAdd(stack, &digit);
  }

  while (!isStackEmpty(stack)) {
    Token tkn;
    stackPop(stack, &tkn);

    printf("op: %d\n", tkn.op);
  }

  return 0;
}
