#include "char_utils.h"

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
