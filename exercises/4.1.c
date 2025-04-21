#include "../lib/asserts.h"
#include "stdio.h"

int strrindex(char *s, char *t) {
  int res = -1;

  int i = 0;
  while (s[i] != '\0') {
    if (s[i] != t[0]) {
      i++;
      continue;
    }

    const int startSeq = i;

    int j = 0;
    while (s[i] == t[j] && t[j] != '\0') {
      i++;
      j++;
    }

    if (t[j] == '\0' && (s[i - 1] == t[j - 1])) {
      res = startSeq;
    }
  }

  return res;
}

int main() {
  assertEquals("Fint last index of 'g' int strind:  'Test g9 697 g, h'", 12,
               strrindex("Test g9 697 g, h", "g"));
  assertEquals(
      "Find last index of 'hello worlds' in sting: 'hello wolrd, hello "
      "world, "
      "hello word'",
      13, strrindex("hello wolrd, hello world, hello word", "hello world"));
  assertEquals("Fint last index of '1' int strind:  'No ones in this string'",
               -1, strrindex("No ones in this string", "1"));
  assertEquals("Find total equality", 0,
               strrindex("Total equals", "Total equals"));

  return 0;
}
