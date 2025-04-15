#include "float.h"
#include "limits.h"
#include "stdio.h"

int main() {
  printf("Char len bites: %d\n", CHAR_BIT);
  printf("Char max len: %d\n", CHAR_MAX);
  printf("Char min len: %d\n", CHAR_MIN);
  printf("Int max len: %d\n", INT_MAX);
  printf("Int min len: %d\n", INT_MIN);
  printf("Short int max: %d\n", SHRT_MAX);
  printf("Short int min: %d\n", SHRT_MIN);
  printf("Long bit size: %d\n", LONG_BIT);
  printf("Long int max len: %ld\n", LONG_MAX);
  printf("Long int min len: %ld\n", LONG_MIN);

  return 0;
}
