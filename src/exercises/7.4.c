#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int read_digit(char *);
void minscanf(const char *, ...);

int main() {
  int test;
  minscanf("day: %d", &test);

  return 0;
}

void minscanf(const char *pattern, ...) {
  va_list ap;
  va_start(ap, pattern);

  char buf[100];

  while (*pattern != '\0') {
    if (*pattern != '%') {
      const int ch = getc(stdin);
      if (ch != *pattern) {
        fprintf(stderr, "Unexpected token. Expected: '%c', got '%c'\n",
                *pattern, isprint(ch) ? ch : '\0');
        exit(1);
        return;
      }

      pattern++;
      continue;
    }

    int last_ch;
    switch (*++pattern) {
    case 'd':
      last_ch = read_digit(buf);
      *(va_arg(ap, int *)) = atoi(buf);
      break;
    }

    if (last_ch != EOF) {
      ungetc(last_ch, stdin);
    }

    pattern++;
  }
}

int read_digit(char *digit) {
  int ch;
  while ((ch = getchar()) != EOF && isdigit(ch)) {
    *digit = ch;
    digit++;
  }
  *digit = '\0';

  return ch;
}
