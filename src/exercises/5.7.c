#include <stdio.h>

#define MAX_LEN 20

int readline(char *dest, int max_len) {
  int ch;
  int len = 0;
  while ((ch = getchar()) != EOF && (len < max_len - 1)) {
    if (ch == '\n') {
      break;
    }

    *dest++ = ch;
    len++;
  }

  if (len == 0) {
    return 0;
  }

  *dest++ = '\0';
  len++;

  return len;
}

int readlines(char *dest[MAX_LEN], int max_lines) {
  const int tmp_max_lines = max_lines;

  while (max_lines-- > 0 && readline(dest++, MAX_LEN) > 0) {
  }

  return tmp_max_lines - max_lines - 1;
}

int main() {
  char lines[3][20];
  int lineCount = readlines(lines, 3);
  printf("linecount: %d\n", lineCount);
}
