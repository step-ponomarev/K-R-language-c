#ifndef STACK_H_
#define STACK_H_

typedef struct {
  char *head;
  int capacity;
  int size;
} Stack;

Stack createStack();
void destroyStack(Stack);

void add(Stack *, char);
char pop(Stack *);
char peek(Stack);
char isStackEmpty(Stack);

#endif
