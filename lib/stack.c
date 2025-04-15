#include "stack.h"
#include "array_utils.h"
#include "stdlib.h"

#define INIT_CAPACITY 10
#define EXPAND_FACTOR 2

Stack createStack() {
  return ((Stack){.head = malloc(sizeof(char) * INIT_CAPACITY),
                  .capacity = INIT_CAPACITY,
                  .size = 0});
}

void destroyStack(Stack stack) { free(stack.head); }

void add(Stack *stack, char ch) {
  if (stack->size == stack->capacity) {
    int newCapacity = (int)stack->capacity * EXPAND_FACTOR;
    expand(&stack->head, stack->capacity, newCapacity);
    stack->capacity = newCapacity;
  }

  stack->head[stack->size++] = ch;
}

char pop(Stack *stack) {
  if (stack->size == 0) {
    return -1;
  }

  return stack->head[--stack->size];
}

char peek(Stack stack) {
  if (stack.size == 0) {
    return -1;
  }

  return stack.head[stack.size - 1];
}

char isStackEmpty(Stack stack) { return stack.size == 0; }
