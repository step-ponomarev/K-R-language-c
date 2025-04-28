#include "../lib/buffered_reader.h"
#include "../lib/char_utils.h"
#include "stdio.h"

int getfloat(double *dest, BufferedReader *reader) {
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

  int beforeDotPart = ch - '0';
  char isDot = 0;

  int afterDot = 0;
  double afterDotCoef = 1;
  while ((ch = buffered_reader_get_char(reader)) != EOF &&
         (isDigit(ch) || ch == '.')) {
    if (ch == '.') {
      if (isDot) {
        buffered_reader_unget_char(reader, ch);
        return 0;
      }

      isDot = 1;
      continue;
    }

    if (!isDot) {
      beforeDotPart = beforeDotPart * 10 + (ch - '0');
      continue;
    }

    afterDotCoef *= 0.1;
    afterDot = afterDot * 10 + (ch - '0');
  }

  if (ch != EOF && !isEmpty(ch)) {
    buffered_reader_unget_char(reader, ch);
    return EOF;
  }

  if (ch != EOF) {
    buffered_reader_unget_char(reader, ch);
  }

  double destRes = (afterDotCoef * afterDot) + beforeDotPart;
  *dest = isNegative ? destRes * -1 : destRes;

  return ch;
}

int main() {
  BufferedReader *reader = buffered_reader_create();

  double res;
  while ((getfloat(&res, reader) != EOF)) {
    printf("Parsed: %f\n", res);
  }

  buffered_reader_destroy(reader);

  return 0;
}
