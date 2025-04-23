#ifndef STACK_H_
#define STACK_H_

#include "stddef.h"

typedef struct Stack Stack;

Stack *create_stack(size_t);
void destroy_stack(Stack *);

int stack_add(Stack *, const void *);
int stack_pop(Stack *, void *);
int stack_peek(const Stack *, void *);
int stack_size(const Stack *);
char is_stack_empty(const Stack *);
void stack_clear(Stack *);
int stack_swap_top(Stack *);
int stack_duplicate_top(Stack *);

#endif
