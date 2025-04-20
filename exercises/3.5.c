#include "../lib/asserts.h"
#include "../lib/char_utils.h"
#include "stdlib.h"

char convertDigit(int i) {
  if (i < 0 || i > 9) {
    return -1;
  }

  return '0' + i;
}

char convert(int i) {
  if (i < 0 || i > 15) {
    return -1;
  }

  if (i < 10) {
    return convertDigit(i);
  }

  return 'A' + (i - 10);
}

int bitSize(int i) {
  int res = 0;
  while (i) {
    i >>= 1;
    res++;
  }

  return res;
}

char *itob(int n, int b) {
  char *res = malloc(sizeof(char) * 200);

  const int shift = bitSize(b - 1);
  int i = 0;
  while (n) {
    res[i++] = convert(n & (b - 1));
    n >>= shift;
  }
  res[i] = '\0';

  char *cutRes = substring(res, 0, i);
  reverse(cutRes);
  free(res);

  return cutRes;
}

int main() {
  assertEquals("Convert 12 to binary", "1100", itob(12, 2));
  assertEquals("Convert 12 to binary", "C", itob(12, 16));
  assertEquals("Convert 12 to binary", "4E6BC", itob(321212, 16));

  return 0;
}
