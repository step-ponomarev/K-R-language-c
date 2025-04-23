#include "../lib/asserts.h"
#include "../lib/char_utils.h"
#include "limits.h"
#include "stdio.h"
#include "stdlib.h"

char convert(int i) {
  if (i < 0 || i > 9) {
    return -1;
  }

  return '0' + i;
}

int max(int a, int b) { return a >= b ? a : b; }

char *itoa(int n, int min) {
  unsigned int unsignedN = n >= 0 ? n : (n * -1);
  const char valueIsNegative = n < 0;

  int size = max(20, min);
  char *res = malloc(sizeof(char) * (max(20, min) + 1));
  int i = 0;

  if (unsignedN >= 0 && unsignedN < 10) {
    if (valueIsNegative) {
      res[i++] = '-';
    }
    res[i++] = convert(unsignedN);
    while (i < min) {
      res[i++] = ' ';
    }
    res[i] = '\0';

    return res;
  }

  do {
    res[i++] = convert(unsignedN % 10);
    unsignedN /= 10;
  } while (unsignedN);

  if (valueIsNegative) {
    res[i++] = '-';
  }
  res[i] = '\0';

  reverse(res);
  while (i < min) {
    res[i++] = ' ';
  }
  res[i] = '\0';

  return res;
}

int main() {
  assertEquals("Test 10", "10 ", itoa(10, 3));
  assertEquals("Test -1", "-1", itoa(-1, -1));
  assertEquals("Test 2228881", "2228881", itoa(2228881, -1));
  assertEquals("Test -9", "-9 ", itoa(-9, 3));
  assertEquals("Test min integer %d", "-2147483648   ", itoa(INT_MIN, 14));
}
