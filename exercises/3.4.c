#include "../lib/asserts.h"
#include "../lib/char_utils.h"
#include "limits.h"
#include "stdlib.h"

char convert(int i) {
  if (i < 0 || i > 9) {
    return -1;
  }

  return '0' + i;
}

char *itoa(int n) {
  unsigned int unsignedN = n >= 0 ? n : (n * -1);
  const char valueIsNegative = n < 0;

  char *res = malloc(sizeof(char) * 20);
  int i = 0;

  if (unsignedN >= 0 && unsignedN < 10) {
    if (valueIsNegative) {
      res[i++] = '-';
    }
    res[i++] = convert(unsignedN);
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

  return res;
}

int main() {
  assertEquals("Test 10", "10", itoa(10));
  assertEquals("Test -1", "-1", itoa(-1));
  assertEquals("Test 2228881", "2228881", itoa(2228881));
  assertEquals("Test -99991212", "-99991212", itoa(-99991212));
  assertEquals("Test min integer %d", "-2147483648", itoa(INT_MIN));
}
