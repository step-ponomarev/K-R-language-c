#include "../lib/asserts.h"
#include "../lib/char_utils.h"
#include "stdlib.h"
/*
  cc ../lib/char_utils.c ../lib/asserts.c ./2.4.c -o main && ./main && rm -rf
  ./main
 */

#define ASCI_SIZE 256

char *squeeze(char s1[], char s2[]) {
  const int secondStrLen = lengthOf(s2);

  char skipSymbolTable[ASCI_SIZE] = {0};
  for (int i = 0; i < secondStrLen; i++) {
    skipSymbolTable[s2[i]] = 1;
  }

  const int firstStrLen = lengthOf(s1);
  char *res = malloc(sizeof(char) * firstStrLen + 1);
  int wPtr = 0;
  for (int rPtr = 0; rPtr < firstStrLen; rPtr++) {
    char curr = s1[rPtr];
    if (skipSymbolTable[curr] == 1) {
      continue;
    }

    res[wPtr++] = curr;
  }
  res[wPtr] = '\0';

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
