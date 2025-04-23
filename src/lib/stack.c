#include "stack.h"
#include "stdlib.h"
#include "string.h"
#include <stddef.h>
#include <stdlib.h>

struct Stack {
  void *head;
  int capacity;
  int size;
  size_t elementSize;
};

#define INIT_CAPACITY 20
#define EXPAND_FACTOR 2

void stash_stack(Stack *stack, size_t elementSize) {
  if (!stack) {
    return;
  }

  if (stack->head) {
    free(stack->head);
  }

  stack->head = malloc(sizeof(elementSize) * INIT_CAPACITY);
  stack->capacity = INIT_CAPACITY;
  stack->size = 0;
  stack->elementSize = elementSize;
}

Stack *create_stack(size_t elementSize) {
  Stack *stack = malloc(sizeof(Stack));
  if (!stack) {
    return NULL;
  }

  stash_stack(stack, elementSize);

  return stack;
}

void destroy_stack(Stack *stack) {
  if (!stack) {
    return;
  }

  if (stack->head) {
    free(stack->head);
  }

  free(stack);
}

int stack_add(Stack *stack, const void *element) {
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

int stack_pop(Stack *stack, void *dest) {
  if (stack->size == 0) {
    return -1;
  }

  const int peekRes = stack_peek(stack, dest);
  if (peekRes != 0) {
    return peekRes;
  }

  stack->size--;

  return 0;
}

int stack_peek(const Stack *stack, void *dest) {
  if (stack->size == 0) {
    return -1;
  }

  memcpy(dest, stack->head + (stack->elementSize * (stack->size - 1)),
         stack->elementSize);

  return 0;
}

int stack_duplicate_top(Stack *stack) {
  if (!stack || stack->size == 0) {
    return -1;
  }

  void *duplicate = malloc(stack->elementSize);
  if (stack_peek(stack, duplicate) != 0) {
    return -1;
  }

  if (stack_add(stack, duplicate) != 0) {
    return -1;
  }

  free(duplicate);

  return 0;
}

void stack_clear(Stack *stack) {
  if (!stack) {
    return;
  }

  stash_stack(stack, stack->elementSize);
}

int stack_swap_top(Stack *stack) {
  if (stack->size < 2) {
    return -1;
  }

  void *first = malloc(stack->elementSize);
  stack_pop(stack, first);

  void *second = malloc(stack->elementSize);
  stack_pop(stack, second);

  stack_add(stack, first);
  stack_add(stack, second);

  free(first);
  free(second);

  return 0;
}

int stack_size(const Stack *stack) { return stack->size; }

char is_stack_empty(const Stack *stack) { return stack->size == 0; }
