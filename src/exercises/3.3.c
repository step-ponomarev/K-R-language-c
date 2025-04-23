#include "../lib/asserts.h"
#include "stdio.h"
#include "stdlib.h"

#define RANGE_OPERATOR_SYMBOL '-'
#define SEQ_SYMBOL ','

int max(int a, int b) { return a <= b ? b : a; }

int min(int a, int b) { return a <= b ? a : b; }

char *expand(char *s) {
  char *res = malloc(sizeof(char) * 200);
  int wPtr = 0;
  int i = 0;

  if (s[i] == RANGE_OPERATOR_SYMBOL) {
    res[wPtr++] = s[i++];
  }

  while (s[i] != '\0') {
    char start = s[i++];
    char op = s[i++];
    if (op == SEQ_SYMBOL) {
      res[wPtr++] = start;
      continue;
    }

    if (op == '\0') {
      res[wPtr++] = start;
      break;
    }

    char end = s[i++];
    if (end == '\0') {
      res[wPtr++] = start;
      res[wPtr++] = RANGE_OPERATOR_SYMBOL;
      break;
    }

    while (s[i] != '\0') {
      if (s[i] == RANGE_OPERATOR_SYMBOL) {
        i++;
        continue;
      }

      if (s[i] == SEQ_SYMBOL) {
        i++;
        break;
      }

      end = s[i++];
    }

    for (int j = min(start, end); j <= max(start, end); j++) {
      res[wPtr++] = j;
    }

    if (s[i] == '\0' && s[i - 1] == RANGE_OPERATOR_SYMBOL) {
      res[wPtr++] = RANGE_OPERATOR_SYMBOL;
    }
  }
  res[wPtr++] = '\0';

  char *cutRes = malloc(sizeof(char) * wPtr);
  for (int i = 0; i < wPtr; i++) {
    cutRes[i] = res[i];
  }

  free(res);

  return cutRes;
}

int main() {
  assertEquals("Basic expand test 'a-c'", "abc", expand("a-c"));
  assertEquals("Basic expand digit test '1-5'", "12345", expand("1-5"));
  assertEquals("Expand tripe 1-5-8-9", "123456789", expand("1-5-8-9"));
  assertEquals("Expand seq 1-3,7-9", "123789", expand("1-3,7-9"));
  assertEquals("Expand single seq 1,2,3,4", "1234", expand("1,2,3,4"));
  assertEquals("Start by range symbol -1,3,4", "-134", expand("-1,3,4"));
  assertEquals("End by range symbol 1,3,4-", "134-", expand("1,3,4-"));
}
