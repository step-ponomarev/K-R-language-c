#ifndef ASSERTS_H_
#define ASSERTS_H_

__attribute__((overloadable)) void assertEquals(char[], int, int);
__attribute__((overloadable)) void assertEquals(char[], double, double);
__attribute__((overloadable)) void assertEquals(char[], char[], char[]);

#endif
