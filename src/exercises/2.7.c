#include "../lib/asserts.h"

int invert(int x, int p, int n) {
  const int shift = p - n + 1;
  const int nFirstOnes = ~(~0 << n);
  const int invertedBites = (~(x >> shift) & nFirstOnes);
  const int pZeros = (~nFirstOnes << shift | ~(~0 << shift));
  const int pInvertedBites = invertedBites << shift;

  return x & pZeros | pInvertedBites;
}

int main() {
  assertEquals("Test x: 0b11111, p: 3, n: 2", 0b10011, invert(0b11111, 3, 2));
  assertEquals("Test x: 0b10101, p: 4, n: 0", 0b10101, invert(0b10101, 4, 0));
  assertEquals("Test x: 0b10100001, p: 7, n: 4", 0b01010001,
               invert(0b10100001, 7, 4));

  return 0;
}
