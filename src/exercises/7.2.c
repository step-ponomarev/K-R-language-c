#include <ctype.h>
#include <stdio.h>

#define MAX_LINE_LEN 10

int main() {
  int ch;
  int len = 0;
  while ((ch = getc(stdin)) != EOF) {
    const char print_symbol = isprint(ch);
    if (!print_symbol) {
      printf("%o", ch);
    } else {
      printf("%c", ch);
    }

    len++;
    if (len == MAX_LINE_LEN) {
      printf("\n");
      len = 0;
    }
  }

  return 0;
}
