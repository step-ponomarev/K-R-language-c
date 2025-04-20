#include "../lib/asserts.h"
#include "stdlib.h"
#include <stdlib.h>

#define OPERATOR_SYMBOL_START '\\'

void escape(char *s, char *t) {
  int rPtr = 0;
  int wPtr = 0;

  while (t[rPtr] != '\0') {
    if (t[rPtr] != OPERATOR_SYMBOL_START) {
      s[wPtr++] = t[rPtr++];
      continue;
    }

    const char next = t[++rPtr];
    switch (next) {
    case 'n':
      s[wPtr++] = '\n';
      break;
    case 't':
      s[wPtr++] = '\t';
      break;
    default:
      s[wPtr++] = OPERATOR_SYMBOL_START;
      s[wPtr++] = next;
    }
    rPtr++;
  }

  s[wPtr] = '\0';
}

char *toCharSeq(char *str) {
  int len = 0;
  while (str[len++] != '\0') {
  }

  char *data = malloc(sizeof(char) * (len));
  for (int i = 0; i <= len; i++) {
    data[i] = str[i];
  }

  return data;
}

int main() {
  char *toModify = malloc(sizeof(char) * 200);

  escape(toModify, "\\n");
  assertEquals("Test simple '\\n'", "\n", toModify);

  escape(toModify, "My test is\\tvery high \\r bb\\n");
  assertEquals("Test 'My test is\\tvery high \\r bb\\n'",
               "My test is\tvery high \\r bb\n", toModify);

  free(toModify);
}
