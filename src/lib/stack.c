#include "stack.h"
#include "stdlib.h"
#include "string.h"

struct Stack {
  void *head;
  int capacity;
  int size;
  size_t elementSize;
};

#define INIT_CAPACITY 20
#define EXPAND_FACTOR 2

Stack *createStack(size_t elementSize) {
  Stack *stack = malloc(sizeof(Stack));
  if (!stack) {
    return NULL;
  }

  stack->head = malloc(sizeof(elementSize) * INIT_CAPACITY);
  stack->capacity = INIT_CAPACITY;
  stack->size = 0;
  stack->elementSize = elementSize;

  return stack;
}

void destroyStack(Stack *stack) {
  if (!stack) {
    return;
  }

  if (stack->head) {
    free(stack->head);
  }

  free(stack);
}

int stackAdd(Stack *stack, const void *element) {
  if (stack->size == stack->capacity) {
    int newCapacity = (int)stack->capacity * EXPAND_FACTOR;
    stack->head = realloc(stack->head, newCapacity * stack->elementSize);
    stack->capacity = newCapacity;
  }

  void *targetPos = stack->head + (stack->elementSize * stack->size);
  memcpy(targetPos, element, stack->elementSize);
  stack->size++;

  return 0;
}

int stackPop(Stack *stack, void *dest) {
  if (stack->size == 0) {
    return -1;
  }

  const int peekRes = stackPeek(stack, dest);
  if (peekRes != 0) {
    return peekRes;
  }

  stack->size--;

  return 0;
}

int stackPeek(const Stack *stack, void *dest) {
  if (stack->size == 0) {
    return -1;
  }

  memcpy(dest, stack->head + (stack->elementSize * (stack->size - 1)),
         stack->elementSize);

  return 0;
}

char isStackEmpty(const Stack *stack) { return stack->size == 0; }
