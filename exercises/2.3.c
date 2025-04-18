#include "../lib/iolib.h"
#include "stdio.h"
#include <stdio.h>

#define GREEN_COLOR 32
#define RED_COLOR 31

char isSupported(char ch) {
  if (ch >= '0' && ch <= '9') {
    return 1;
  }

  if (ch >= 'a' && ch <= 'f') {
    return 1;
  }

  if (ch >= 'A' && ch <= 'F') {
    return 1;
  }

  return 0;
}

char isValidHex(String word) {
  if (word.length == 0) {
    return 0;
  }

  char *str = word.str;
  if (word.length == 1) {
    return isSupported(str[0]);
  }

  if (word.length == 2) {
    return isSupported(str[0]) && isSupported(str[1]);
  }

  int i = 0;
  if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
    i = 2;
  }

  while (i < word.length) {
    if (!isSupported(str[i++])) {
      return 0;
    }
  }

  return 1;
}

int htoi(String s) { return 0; }

void assert(char desc[], int expected, int actual) {
  printf("\033[%dm%s:\nExpexted: %d, actual: %d\n\n",
         expected == actual ? GREEN_COLOR : RED_COLOR, desc, expected, actual);
}

int main() {
  printf("Test hex validation:\n");
  assert("Check valid hex with small prefix", 1,
         isValidHex(createString("0xF")));
  assert("Check valid hex with capital prefix", 1,
         isValidHex(createString("0XF")));
  assert("Check valid hex without prefix string", 1,
         isValidHex(createString("F")));
  assert("Check invalid hex with prefix", 0,
         isValidHex(createString("0x9328823G")));

  printf("Test htoi:\n");
  assert("Test small x prefix conversion", 15, htoi(createString("0xF")));
  assert("Test capital X prefix conversion", 15, htoi(createString("0XF")));
  assert("Test without prefix conversion", 15, htoi(createString("F")));
  assert("Test invalid hex value", 0, htoi(createString("G")));

  return 0;
}
