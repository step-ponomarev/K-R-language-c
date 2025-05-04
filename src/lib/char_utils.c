#include "char_utils.h"
#include "stdlib.h"
#include <stdio.h>

char isEmpty(char ch) { return ch == ' ' || ch == '\t' || ch == '\n'; }

char isEquals(const char *s1, const char *s2) {
  for (; *s1 == *s2; s1++, s2++) {
    if (*s1 == '\0') {
      return 1;
    }
  }

  return 0;
}

int string_compare(const char *s1, const char *s2) {
  for (; *s1 == *s2; s1++, s2++) {
    if (*s1 == '\0') {
      return 0;
    }
  }

  return *s1 < *s2 ? -1 : 1;
}

char toCapital(const char ch) {
  return (ch >= 'a' && ch <= 'z' ? (ch - 'a' + 'A') : ch);
}

char char_compare_ignore_case(const char ch1, const char ch2) {
  const char Ch1 = toCapital(ch1);
  const char Ch2 = toCapital(ch2);

  if (Ch1 == Ch2) {
    return 0;
  }

  return Ch1 < Ch2 ? -1 : 1;
}

int string_compare_ignore_register(const char *s1, const char *s2) {
  for (; char_compare_ignore_case(*s1, *s2) == 0; s1++, s2++) {
    if (*s1 == '\0') {
      return 0;
    }
  }

  return char_compare_ignore_case(*s1, *s2);
}

int lengthOf(char str[]) {
  int i = 0;
  while (str[i++] != '\0') {
  }

  return i;
}

int copy_string(const char src[], char **dest) {
  int len = 0;
  while (src[len] != '\0') {
    len++;
  }

  *dest = malloc(sizeof(char) * (len + 1));
  for (int i = 0; i <= len; i++) {
    (*dest)[i] = src[i];
  }

  return len;
}

// 12345 [1, 3)
char *substring(char *line, int startIndex, int endIndex) {
  int stirngLen = endIndex - startIndex;

  // stirng len + \0
  char *newLine = malloc(sizeof(char) * (stirngLen + 1));
  for (int i = 0; i < stirngLen; i++) {
    newLine[i] = line[startIndex++];
    if (newLine[i] == '\0') {
      return newLine;
    }
  }
  newLine[stirngLen] = '\0';

  return newLine;
}

char *trim(char *line) {
  int startIndex = -1;
  int endIndex = 0;

  while (line[endIndex] != '\0') {
    if (startIndex != -1) {
      endIndex++;
      continue;
    }

    while (isEmpty(line[endIndex])) {
      endIndex++;
    }

    startIndex = endIndex;
  }
  endIndex--;

  while (endIndex > 0 && isEmpty(line[endIndex])) {
    endIndex--;
  }

  return substring(line, startIndex, endIndex + 1);
}

char isBlank(char *line) {
  int i = 0;
  while (line[i] != '\0') {
    if (!isEmpty(line[i])) {
      return 0;
    }
    i++;
  }

  return 1;
}

char isDigit(char ch) { return ch >= '0' && ch <= '9'; }

void reverse(char *str) {
  int end = 0;
  while (str[end] != '\0') {
    end++;
  }

  end--;
  int start = 0;
  while (start < end) {
    char tmp = str[end];
    str[end] = str[start];
    str[start] = tmp;
    start++;
    end--;
  }
}
