#include <__stdarg_va_list.h>
#include <stdarg.h>
#include <stdio.h>

void minprintf(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  while (*fmt != '\0') {
    if (*fmt != '%') {
      putc(*fmt, stdout);
      fmt++;
      continue;
    }

    switch (*++fmt) {
    case 'd':
      printf("%d", va_arg(ap, int));
      break;
    case 's':
      printf("%s", va_arg(ap, char *));
      break;
    }

    fmt++;
  }
}

int main() {
  minprintf("Hello, friend %d %s\n", 123, "omggg");
  minprintf("Hello, friend %d\n", 123141);

  return 0;
}
