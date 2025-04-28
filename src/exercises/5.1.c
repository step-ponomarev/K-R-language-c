#include "../lib/asserts.h"
#include "../lib/buffered_reader.h"
#include "../lib/char_utils.h"
#include <stdio.h>

int getint(int *dest, BufferedReader *reader) {
  int ch;
  while (((ch = buffered_reader_get_char(reader)) != EOF) && isEmpty(ch)) {
  }

  if (ch != EOF && !isDigit(ch) && ch != '-' && ch != '+') {
    buffered_reader_unget_char(reader, ch);
    return 0;
  }

  const char isSign = ch == '+' || ch == '-';
  const char isNegative = isSign && ch == '-';

  if (isSign && !isDigit((ch = buffered_reader_get_char(reader)))) {
    buffered_reader_unget_char(reader, ch);
    return 0;
  }

  int res = ch - '0';
  int i = 1;
  while ((ch = buffered_reader_get_char(reader)) != EOF && isDigit(ch)) {
    res = res * 10 + (ch - '0');
    i++;
  }

  if (ch != EOF && !isEmpty(ch)) {
    buffered_reader_unget_char(reader, ch);
    return EOF;
  }

  if (ch != EOF) {
    buffered_reader_unget_char(reader, ch);
  }

  *dest = isNegative ? res * -1 : res;

  return ch;
}

int main() {
  BufferedReader *reader = buffered_reader_create();

  int res;
  while ((getint(&res, reader) != EOF)) {
    printf("Parsed: %d\n", res);
  }

  buffered_reader_destroy(reader);

  return 0;
}
