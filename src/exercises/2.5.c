#include "../lib/asserts.h"
#include "../lib/char_utils.h"
#include "stdio.h"

#define ASCI_SIZE 256

char *any(char s1[], char s2[]) {
  const int s2Len = lengthOf(s2);
  char foundSymbolTable[ASCI_SIZE] = {0};
  for (int i = 0; i < s2Len; i++) {
    foundSymbolTable[s2[i]] = 1;
  }

  const int s1Len = lengthOf(s1);
  for (int i = 0; i < s1Len; i++) {
    if (foundSymbolTable[s1[i]]) {
      return &(s1[i]);
    }
  }

  char *ptr = NULL;

  return ptr;
}

int main() {
  assertEquals("Test s1: 'hello world', s2: 'w'", "world",
               any("hello world", "w"));

  assertEquals("Test s1: 'any', s2: 'e'", 0, *any("any", "e"));

  return 0;
}
