#include "stack.h"
#include "stdlib.h"
#include "array_utils.h"

#define INIT_CAPACITY 10
#define EXPAND_FACTOR 2

struct Stack createStack() {
    return ((struct Stack) {
        .head = malloc(sizeof(char) * INIT_CAPACITY),
        .capacity = INIT_CAPACITY,
        .size = 0
    });
}

void destroyStack(struct Stack stack) {
    free(stack.head);
}

void add(struct Stack* stack, char ch) {
    if (stack->size == stack->capacity) {
        int newCapacity = (int) stack->capacity * EXPAND_FACTOR;
        expand(&stack->head, stack->capacity, newCapacity);
        stack->capacity = newCapacity;
    }

    stack->head[stack->size++] = ch;
}


char pop(struct Stack* stack) {
    if (stack->size == 0) {
        return -1;
    }

    return stack->head[--stack->size];
}

char peek(struct Stack stack) {
    if (stack.size == 0) {
        return - 1;
    }

    return stack.head[stack.size - 1];
}

char isStackEmpty(struct Stack stack) {
    return stack.size == 0;
}