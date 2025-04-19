#include "../lib/asserts.h"

short int bitcount(unsigned int x) {
  if (x == 0) {
    return 0;
  }

  int res = 1;
  while (x &= (x - 1)) {
    res++;
  }

  return res;
}

// Док-во:
// 11110 - 1-> 11101 & 11110 = 11100
// 11000 - 1 -> 10111 & 11000 = 10000
int main() {
  assertEquals("Test count bits of 0b101", 2, bitcount(0b101));
  assertEquals("Test count bits of 0b11111011", 7, bitcount(0b11111011));
  return 0;
}
