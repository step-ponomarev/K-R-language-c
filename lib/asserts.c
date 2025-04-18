#include "asserts.h"
#include "stdio.h"

#define GREEN_COLOR 32
#define RED_COLOR 31

void assert(char desc[], int expected, int actual) {
  printf("\033[%dm%s:\nExpexted: %d, actual: %d\n\n",
         expected == actual ? GREEN_COLOR : RED_COLOR, desc, expected, actual);
}
