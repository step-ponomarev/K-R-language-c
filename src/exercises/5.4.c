#include "../lib/asserts.h"

char strend(const char *s, const char *t) {
  const char *tStart = t;

  while (*s != '\0') {
    if (*s++ != *t++) {
      t = tStart;
    }
  }

  return *t == '\0';
}

void basicPositiveTest() {
  char str1[] = "123456789";
  char str2[] = "789";

  assertEquals("Basic positive test", 1, strend(str1, str2));
}

void basicNegatieTest() {
  char str1[] = "123456789";
  char str2[] = "788";

  assertEquals("Basic positive test", 0, strend(str1, str2));
}

void equalsStringsTest() {
  char str1[] = "123456789";
  char str2[] = "123456789";

  assertEquals("Basic positive test", 1, strend(str1, str2));
}

int main() {
  basicPositiveTest();
  basicNegatieTest();
  equalsStringsTest();

  return 0;
}
