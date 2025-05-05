#include <ctype.h>
#include <stdio.h>

char is_upper(const char *);

int main(const int argc, const char *argv[]) {
  const char prog_name_is_upper = is_upper(argv[0]);

  int ch;
  while ((ch = getc(stdin)) != EOF) {
    putc(prog_name_is_upper ? toupper(ch) : tolower(ch), stdout);
  }

  return 0;
}

char is_upper(const char *line) {
  while (!isalpha(*line)) {
    line++;
  }

  while (*line != '\0') {
    if (!isupper(*line)) {
      return 0;
    }

    line++;
  }

  return 1;
}
