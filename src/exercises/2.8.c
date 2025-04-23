#include "../lib/asserts.h"
#include "limits.h"

int rightrot(char x, char n) {
  const char firstNOnes = ~(~0 << n);
  const char firstNbites = x & firstNOnes;
  const char rotatedFirstBits = firstNbites << (CHAR_BIT - n - 1);

  return (x >> n) | rotatedFirstBits;
}

int main() {
  assertEquals("Test x: 0b00000101, n: 3", 0b1010000, rightrot(0b101, 3));
  assertEquals("Test x: 0b00010001 -> 0b0100100, n: 2", 0b0100100,
               rightrot(0b00010001, 2));
}
