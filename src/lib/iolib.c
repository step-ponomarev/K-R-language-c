#include "iolib.h"
#include "char_utils.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdlib.h>

#define INIT_LINE_LEN 100
#define INIT_WORD_LEN 10
#define EXPAND_COEF 2

int readline(char *dist) {
  if (!dist) {
    return -1;
  }

  int currLen = INIT_LINE_LEN;
  char *chArr = malloc(sizeof(char) * (currLen + 1));
  int i = 0;

  int ch;
  while (((ch = getchar()) != EOF) && (ch != '\n')) {
    if (i == currLen - 1) {
      int newLen = (int)(currLen * EXPAND_COEF);
      chArr = realloc(chArr, sizeof(char) * newLen);
      currLen = newLen;
    }

    chArr[i++] = ch;
  }
  chArr[i] = '\0';

  memcpy(dist, chArr, sizeof(char) * (i + 1));
  free(chArr);

  return i;
}

int read_word(char *dist) {
  if (!dist) {
    return -1;
  }

  int currLen = INIT_WORD_LEN;

  // skip start empty
  int ch;
  while ((ch = getchar()) != EOF && (isEmpty(ch))) {
  }

  if (ch == EOF) {
    return 0;
  }

  char *chArr = malloc(sizeof(char) * (currLen + 1));
  chArr[0] = ch;
  int i = 1;

  while ((ch = getchar()) != EOF) {
    if (i == currLen - 1) {
      int newLen = (int)(currLen * EXPAND_COEF);
      chArr = realloc(chArr, sizeof(char) * newLen);
      currLen = newLen;
    }

    if (isEmpty(ch)) {
      break;
    }

    chArr[i++] = ch;
  }
  chArr[i] = '\0';

  memcpy(dist, chArr, sizeof(char) * (i + 1));
  free(chArr);

  return i;
}
