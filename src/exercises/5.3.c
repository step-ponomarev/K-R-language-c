#include "../lib/asserts.h"
#include <stdio.h>

void strcat(char *s, char *t) {
  char *startTAddr = t;

  while (*s != '\0') {
    s++;

    if (*t != '\0') {
      t++;
    }
  }

  while (t >= startTAddr) {
    *s-- = *t--;
  }
}

int main() {
  char str1[] = "22888";
  char str2[] = "000";

  strcat(str1, str2);
  assertEquals("Basic test", "22000", str1);

  char str1_1[] = "228";
  char str2_2[] = "228";
  strcat(str1_1, str2_2);

  assertEquals("Equals str", "228", str1_1);

  return 0;
}
