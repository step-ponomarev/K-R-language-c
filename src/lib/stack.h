#ifndef STACK_H_
#define STACK_H_

#include "stddef.h"

typedef struct Stack Stack;

Stack *createStack(size_t);
void destroyStack(Stack *);

int stackAdd(Stack *, const void *);
int stackPop(Stack *, void *);
int stackPeek(const Stack *, void *);
char isStackEmpty(const Stack *);

#endif
