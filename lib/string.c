#include "string.h"
#include "char_utils.h"
#include "stdlib.h"

String createString(char *ch) {
  int len = 0;
  while (ch[len] != '\0') {
    len++;
  }

  char *str = malloc(sizeof(char) * len);
  for (int i = 0; i <= len; i++) {
    str[i] = ch[i];
  }

  return ((String){.str = str, .length = len});
}

void destroyString(String string) { free(string.str); }

String substring(String string, int from, int to) {
  if (from < 0 || to > string.length || to <= from) {
    String errorString = {.str = NULL, .length = -1};

    return errorString;
  }

  int newLen = to - from;
  char *newStr = malloc(sizeof(char) * newLen + 1);
  for (int i = from; i < to; i++) {
    newStr[i - from] = string.str[i];
  }
  newStr[to] = '\0';

  return ((String){.str = newStr, .length = newLen});
}

String trim(String str) {
  int start = 0;
  int end = str.length - 1;
  while (end >= 0) {
    if (!isEmpty(str.str[end])) {
      break;
    }
  }

  end++;
  if (end == 0) {
    char *emptyString = malloc(sizeof(char));
    emptyString[0] = '\0';

    return ((String){.str = emptyString, .length = 0});
    ;
  }

  while (start < str.length) {
    if (!isEmpty(str.str[start])) {
      break;
    }
    start++;
  }

  return substring(str, start, end);
}

char isBlank(String string) {
  if (string.str == NULL || string.length == 0) {
    return 1;
  }

  int start = 0;
  int end = string.length - 1;

  while (start <= end) {
    if (!isEmpty(string.str[start++]) || !isEmpty(string.str[end--])) {
      return 0;
    }
  }

  return 1;
}
