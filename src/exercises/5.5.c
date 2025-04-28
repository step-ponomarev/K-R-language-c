#include "../lib/asserts.h"
#include <stdio.h>

void strncpy(char *s, const char *t, int n) {
  while (n-- > 0 && *t != '\0') {
    *s++ = *t++;
  }
}

void strncat(char *s, const char *t, int n) {
  const char *tStart = t;
  while (*s != '\0') {
    s++;

    if (*t != '\0' && n - 1 > 0) {
      t++;
      n--;
    }
  }

  if (*t != '\0') {
    s--;
  }

  while (t >= tStart) {
    *s-- = *t--;
  }
}

int strncmp(const char *s, const char *t, int n) {
  int res = 0;
  while ((res = (*s++ - *t++)) == 0 && (n > 1)) {
    n--;
  };

  return res;
}

void strncpyTest() {
  char str1[] = "123456789";
  char str2[] = "987654321";
  const int n = 3;

  strncpy(str1, str2, n);

  assertEquals("Test strncpy", "987456789", str1);
}

void strncatTest() {
  char str1[] = "123456789";
  char str2[] = "987654321";
  const int n = 3;

  strncat(str1, str2, n);

  assertEquals("Test strncat", "123456987", str1);
}

void strncmpTest() {
  char str1[] = "123456789";
  char str2[] = "123654321";
  const int n = 3;

  assertEquals("Test equals", 0, strncmp(str1, str2, n));
}

int main() {
  strncpyTest();
  strncatTest();
  strncmpTest();

  return 0;
}
