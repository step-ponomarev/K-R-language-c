#include "../lib/asserts.h"

int setbits(int x, int p, int n, int y) {
  const unsigned int nFirst = ~(~0 << n);
  const int rightBits = nFirst & y;

  const int pDiffN = p - n + 1;
  const int zerosOnP = ~nFirst << pDiffN | ~(~0 << pDiffN);
  const int replaceBitsOnP = rightBits << pDiffN | ~(~0 << pDiffN);

  return (x & zerosOnP) | replaceBitsOnP;
}

int main() {
  // x: 1001 y: 0111,
  assertEquals("Test x: 1001, n: 2, p: 2, y 01111", 0b1111,
               setbits(0b1001, 2, 2, 0b0111));
  assertEquals("Test x: 0b111111, n: 3, p: 4, y: 0b100000", 0b100011,
               setbits(0b111111, 4, 3, 0b100000));
  return 0;
}
