#include "stdio.h"
#include <stdio.h>

#define LIM 5

int main() {
  int c = getchar();
  char s[LIM];

  int i = 0;
  while ((i < (LIM - 1)) & (c != EOF) & (c != '\n')) {
    s[i++] = c;
    c = getchar();
  }
  s[i] = '\0';

  printf("%s\n", s);

  return 0;
}
