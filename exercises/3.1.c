#include "../lib/asserts.h"

int binasearch(int x, int v[], int n) {
  int right = n - 1;
  int left = 0;

  int mid;
  while ((v[(mid = (right + left) >> 1)] != x) && (left <= right)) {
    if (v[mid] > x) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return v[mid] == x ? mid : -1;
}

int main() {
  const int arr1[] = {1, 2, 5, 8, 19, 32};
  assertEquals("Test binary search {1, 2, 5, 8, 19, 32}, x:5", 2,
               binasearch(5, arr1, 6));

  assertEquals("Test binary search {1, 2, 5, 8, 19, 32}, x: 220", -1,
               binasearch(220, arr1, 6));

  return 0;
}
