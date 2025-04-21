#include "char_utils.h"
#include "stdio.h"
#include "stdlib.h"

char isEmpty(char ch) { return ch == ' ' || ch == '\t' || ch == '\n'; }

char isEquals(char s1[], char s2[]) {
  char res = 1;

  int i = 0;
  while ((res = s1[i] == s2[i]) && (s1[i] != '\0')) {
    i++;
  }

  return res;
}

int lengthOf(char str[]) {
  int i = 0;
  while (str[i++] != '\0') {
  }

  return i;
}

// 12345 [1, 3]
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
