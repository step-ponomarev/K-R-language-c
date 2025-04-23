#include "../lib/asserts.h"
#include "stdlib.h"

char *lower(char str[]) {
  int size = 0;

  while (str[size++] != '\0') {
  }

  char *res = malloc(sizeof(char) * size);
  res[size - 1] = '\0';

  for (int i = 0; i < size; i++) {
    res[i] = (str[i] >= 'A' && str[i] <= 'Z') ? str[i] - 'A' + 'a' : str[i];
  }

  return res;
}

int main() {
  assertEquals("Test 'Hello' to lower", "hello", lower("Hello"));

  return 0;
}
