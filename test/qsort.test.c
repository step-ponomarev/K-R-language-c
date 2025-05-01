#include "../src/lib/asserts.h"
#include "../src/lib/char_utils.h"
#include "../src/lib/sort.h"
#include <stdio.h>
#include <string.h>

int compareInts(int a, int b) {
  if (a == b) {
    return 0;
  }

  return a < b ? -1 : 1;
}

int sortDigits(int *a, int *b) { return compareInts(*a, *b); }

int sortShars(char *ch, char *ch2) { return compareInts(*ch, *ch2); }

void testDigitsSort() {
  const size_t size = 8;
  int value[size] = {11, -120, 200, 6, 5, 3, 2, 0};
  qsort((void *)value, sizeof(int), size, (Comparator *)&sortDigits);

  char isSorted = 1;
  for (int i = 1; i < 8; i++) {
    isSorted &= value[i - 1] <= value[i];
  }

  assertEquals("Digit array is sorted", 1, isSorted);
}

void testSortString() {
  const size_t size = 8;
  char value[size] = {'g', 'a', 'b', 'e', 'h', 'd', 'c', 'f'};
  qsort((void *)value, sizeof(char), size, (Comparator *)&sortShars);

  char isSorted = 1;
  for (int i = 1; i < 8; i++) {
    isSorted &= value[i - 1] <= value[i];
  }

  assertEquals("Char array is sorted", 1, isSorted);
}

void testSortStrings() {
  const size_t size = 4;
  const size_t string_size = 120;
  char value[size][string_size] = {"321", "123456789", "0",
                                   "sjadklsadjlkdsajadksljsadklsajd"};

  qsort(value, string_size, size, (Comparator *)&string_compare);

  char isSorted = 1;
  for (int i = 1; i < size; i++) {
    isSorted &= string_compare(value[i - 1], value[i]) == -1;
  }
  assertEquals("Strings are sorted", 1, isSorted);
}

int main() {
  testDigitsSort();
  testSortString();
  testSortStrings();

  return 0;
}
