#include <stdio.h>
#define swap(t, x, y)                                                          \
  {                                                                            \
    t tmp = x;                                                                 \
    x = y;                                                                     \
    y = tmp;                                                                   \
  }

int main() {
  int x = 0;
  int y = 1;

  printf("Before swap x: %d, y: %d\n", x, y);
  swap(int, x, y);
  printf("After swap x: %d, y: %d\n", x, y);
}
