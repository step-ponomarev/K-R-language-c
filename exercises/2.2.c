#include "stdio.h"

#define LIM 5

int main() {
  int c;
  char s[LIM];

  int i = 0;
  while ((i < (LIM - 1)) & ((c = getchar()) != EOF) & (c != '\n')) {
    s[i++] = c;
  }
  s[i] = '\0';

  printf("%s\n", s);

  return 0;
}
