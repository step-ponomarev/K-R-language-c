#include "asserts.h"
#include "char_utils.h"
#include "stdio.h"

#define GREEN_COLOR 32
#define RED_COLOR 31
#define STANDART_COLOR "\33[0:31m"

__attribute__((overloadable)) void assertEquals(char desc[], int expected,
                                                int actual) {
  printf("\033[%dm* %s: Expexted: %d, actual: %d%s\n",
         expected == actual ? GREEN_COLOR : RED_COLOR, desc, expected, actual,
         STANDART_COLOR);
}

__attribute__((overloadable)) void assertEquals(char desc[], double expected,
                                                double actual) {
  printf("\033[%dm* %s: Expexted: %f, actual: %f%s\n",
         expected == actual ? GREEN_COLOR : RED_COLOR, desc, expected, actual,
         STANDART_COLOR);
}

__attribute__((overloadable)) void assertEquals(char desc[], char expected[],
                                                char actual[]) {
  char equals = isEquals(expected, actual);

  printf("\033[%dm* %s: Expexted: '%s', actual: '%s'%s\n",
         equals ? GREEN_COLOR : RED_COLOR, desc, expected, actual,
         STANDART_COLOR);
}
