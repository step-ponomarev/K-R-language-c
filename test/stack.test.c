#include "../src/lib/stack.h"
#include "../src/lib/asserts.h"
#include "stdio.h"

void invertValueTest() {
  char data[] = "1234567";
  char expected[] = "7654321";
  char actual[8];

  Stack *sut = create_stack(sizeof(char));
  for (int i = 0; i < 7; i++) {
    stack_add(sut, &data[i]);
  }

  int i = 0;
  while (!is_stack_empty(sut)) {
    stack_pop(sut, &actual[i++]);
  }
  actual[i] = '\0';
  destroy_stack(sut);

  assertEquals("Invert value", expected, actual);
}

void duplicateTopTest() {
  const int val = 219;

  Stack *sut = create_stack(sizeof(int));

  stack_add(sut, &val);
  stack_duplicate_top(sut);
  stack_duplicate_top(sut);
  stack_duplicate_top(sut);
  assertEquals("Triple top duplicate", 4, stack_size(sut));

  char valsEqualExpexted = 1;
  while (!is_stack_empty(sut)) {
    int i;
    stack_pop(sut, &i);

    valsEqualExpexted = valsEqualExpexted && (i == val);
  }
  assertEquals("Expected vals in stack", 1, valsEqualExpexted);

  destroy_stack(sut);
}

void swapTopTest() {
  const int val1 = 123;
  const int val2 = 321;

  Stack *sut = create_stack(sizeof(int));
  stack_add(sut, &val1);
  stack_add(sut, &val2);

  int val;
  stack_peek(sut, &val);

  assertEquals("Check top before swap", val2, val);

  stack_swap_top(sut);

  stack_peek(sut, &val);
  assertEquals("Check top after swap", val1, val);
}

void clearStacktest() {
  Stack *sut = create_stack(sizeof(int));

  int i = 0;
  for (; i < 200; i++) {
    stack_add(sut, &i);
  }

  assertEquals("Check size before clear", i, stack_size(sut));
  stack_clear(sut);
  assertEquals("Check size after clear", 0, stack_size(sut));
  assertEquals("Pop after clear", -1, stack_pop(sut, &i));
}

int main() {
  invertValueTest();
  duplicateTopTest();
  swapTopTest();
  clearStacktest();

  return 0;
}
