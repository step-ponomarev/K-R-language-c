#include "asserts.h"
#include "stdio.h"

#define GREEN_COLOR 32
#define RED_COLOR 31
#define STANDART_COLOR "\33[0:31m"

void assertEquals(char desc[], int expected, int actual) {
  printf("\033[%dm* %s: Expexted: %d, actual: %d%s\n",
         expected == actual ? GREEN_COLOR : RED_COLOR, desc, expected, actual,
         STANDART_COLOR);
}
