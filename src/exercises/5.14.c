#include "../lib/buffered_reader.h"
#include "../lib/char_utils.h"
#include "../lib/sort.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_COUNT 20
#define MAX_LINE_LEN 100

#define NUMERIC_SORT 0b0001
#define REVERSE_SORT 0b0010

extern int string_compare(const char *, const char *);
extern char isEquals(const char *, const char *);

int get_flags(int, char *[]);
Comparator *get_comparator(const int);
int digit_strings_compare(const char *, const char *);
int digit_strings_compare_reverse(const char *, const char *);

int digits_compare(const int a, const int b);
int string_compare_reverse(const char *, const char *);

int main(int argc, char *argv[]) {
  const int flags = get_flags(argc, argv);

  char lines[MAX_LINE_COUNT][MAX_LINE_LEN];
  BufferedReader *reader = buffered_reader_create();

  int curr = 0;
  while (curr < MAX_LINE_COUNT) {
    const int len = buffered_reader_get_line(reader, lines[curr], MAX_LINE_LEN);
    if (buffered_reader_is_eof(reader) && len == 0) {
      break;
    }

    if (len == 0) {
      continue;
    }

    curr++;
  }

  qsort(lines, MAX_LINE_LEN, curr, get_comparator(flags));
  for (int i = 0; i < curr; i++) {
    printf("%s,", lines[i]);
  }

  buffered_reader_destroy(reader);
}

int get_flags(int argc, char *argv[]) {
  int res = 0;

  for (int i = 1; i < argc; i++) {
    const char *arg = argv[i];

    if (isEquals("-n", arg)) {
      res |= NUMERIC_SORT;
    }

    if (isEquals("-r", arg)) {
      res |= REVERSE_SORT;
    }
  }

  return res;
}

Comparator *get_comparator(const int flags) {
  if (flags & NUMERIC_SORT) {
    return (Comparator *)(flags & REVERSE_SORT ? &digit_strings_compare_reverse
                                               : &digit_strings_compare);
  }

  return (Comparator *)(flags & REVERSE_SORT ? &string_compare_reverse
                                             : &string_compare);
}

int string_compare_reverse(const char *s1, const char *s2) {
  return string_compare(s2, s1);
}

int digit_strings_compare(const char *s1, const char *s2) {
  return digits_compare(atoi(s1), atoi(s2));
}

int digit_strings_compare_reverse(const char *s1, const char *s2) {
  return digit_strings_compare(s2, s1);
}

int digits_compare(const int a, const int b) {
  return a == b ? 0 : a < b ? -1 : 1;
}
