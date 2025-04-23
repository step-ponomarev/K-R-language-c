#include "../stack.h"
#include "../asserts.h"
#include "stdio.h"

void invertValueTest() {
  char data[] = "1234567";
  char expected[] = "7654321";
  char actual[8];

  Stack *sut = createStack(sizeof(char));
  for (int i = 0; i < 7; i++) {
    stackAdd(sut, &data[i]);
  }

  int i = 0;
  while (!isStackEmpty(sut)) {
    stackPop(sut, &actual[i++]);
  }
  actual[i] = '\0';
  destroyStack(sut);

  assertEquals("Invert value", expected, actual);
}

int main() {
  invertValueTest();

  return 0;
}
