#ifndef STACK_H_
#define STACK_H_

struct Stack {
    char* head;
    int capacity;
    int size;
};

struct Stack createStack();
void destroyStack(struct Stack);

void add(struct Stack*, char);
char pop(struct Stack*);
char peek(struct Stack);
char isStackEmpty(struct Stack);

#endif