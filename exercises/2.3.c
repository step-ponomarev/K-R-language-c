#include "../lib/asserts.h"
#include "../lib/string.h"
/*
  cc ../lib/string.c ../lib/array_utils.c ../lib/char_utils.c ../lib/asserts.c /
 ./2.3.c -o main && ./main && rm -rf ./main
 */

#define HEX_BIT_COUNT 16

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

int powInt(int n, int pow) {
  if (pow == 0) {
    return 1;
  }

  int res = n;
  for (int i = 0; i < pow - 1; i++) {
    res *= n;
  }

  return res;
}

int convertHexToNumber(char ch) {
  if (ch >= '0' && ch <= '9') {
    return ch - '0';
  }

  if (ch >= 'a' && ch <= 'f') {
    return ch - 'a' + 10;
  }

  if (ch >= 'A' && ch <= 'F') {
    return ch - 'A' + 10;
  }

  return -1;
}

int htoi(String s) {
  if (!isValidHex(s)) {
    return -1;
  }

  const char *str = s.str;

  int pos = 0;
  int res = 0;
  int i = s.length - 1;
  while (i >= 0) {
    if (str[i] == 'x' || str[i] == 'X') {
      break;
    }

    res += powInt(HEX_BIT_COUNT, pos++) * convertHexToNumber(str[i--]);
  }

  return res;
}

int main() {
  assertEquals("Check valid hex with small prefix", 1,
               isValidHex(createString("0xF")));
  assertEquals("Check valid hex with capital prefix", 1,
               isValidHex(createString("0XF")));
  assertEquals("Check valid hex without prefix string", 1,
               isValidHex(createString("F")));
  assertEquals("Check invalid hex with prefix", 0,
               isValidHex(createString("0x9328823G")));

  assertEquals("Test small x prefix conversion", 15, htoi(createString("0xF")));
  assertEquals("Test capital X prefix conversion", 15,
               htoi(createString("0XF")));
  assertEquals("Test without prefix conversion", 15, htoi(createString("F")));
  assertEquals("Test invalid hex value", -1, htoi(createString("G")));

  assertEquals("Test longer value", 4094, htoi(createString("FFe")));

  return 0;
}
