#include "../lib/asserts.h"
#include "../lib/string.h"
#include "stdlib.h"

/*
  cc ../lib/string.c ../lib/array_utils.c ../lib/char_utils.c ../lib/asserts.c \
  ./2.4.c -o main && ./main && rm -rf ./main
 */

#define ASCI_SIZE 256

char *squeeze(char s1[], char s2[]) {
  const String str1 = createString(s1);
  const String str2 = createString(s2);

  char skipSymbolTable[ASCI_SIZE] = {0};
  for (int i = 0; i < str2.length; i++) {
    skipSymbolTable[str2.str[i]] = 1;
  }

  char *res = malloc(sizeof(char) * str1.length + 1);
  int wPtr = 0;
  for (int rPtr = 0; rPtr < str1.length; rPtr++) {
    char curr = str1.str[rPtr];
    if (skipSymbolTable[curr] == 1) {
      continue;
    }

    res[wPtr++] = curr;
  }
  res[wPtr] = '\0';

  destroyString(str1);
  destroyString(str2);

  return res;
}

int main() {
  assertEquals("Test removing one symbol s1: 12345, s2: Q23", "145",
               squeeze("12345Q", "Q23"));
  assertEquals("Test second string empty, s1: Full string is expected",
               "Full string is expected",
               squeeze("Full string is expected", ""));

  return 0;
}
