#include "../lib/asserts.h"

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

char isValidHex(const char str[], const int length) {
  if (length == 0) {
    return 0;
  }

  if (length == 1) {
    return isSupported(str[0]);
  }

  if (length == 2) {
    return isSupported(str[0]) && isSupported(str[1]);
  }

  int i = 0;
  if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
    i = 2;
  }

  while (i < length) {
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

int htoi(const char str[], const int length) {
  if (!isValidHex(str, length)) {
    return -1;
  }

  int pos = 0;
  int res = 0;
  int i = length - 1;
  while (i >= 0) {
    if (str[i] == 'x' || str[i] == 'X') {
      break;
    }

    res += powInt(HEX_BIT_COUNT, pos++) * convertHexToNumber(str[i--]);
  }

  return res;
}

int main() {
  assertEquals("Check valid hex with small prefix", 1, isValidHex("0xF", 3));
  assertEquals("Check valid hex with capital prefix", 1, isValidHex("0XF", 3));
  assertEquals("Check valid hex without prefix string", 1, isValidHex("F", 1));
  assertEquals("Check invalid hex with prefix", 0,
               isValidHex("0x9328823G", 10));

  assertEquals("Test small x prefix conversion", 15, htoi("0xF", 3));
  assertEquals("Test capital X prefix conversion", 15, htoi("0XF", 3));
  assertEquals("Test without prefix conversion", 15, htoi("F", 1));
  assertEquals("Test invalid hex value", -1, htoi("G", 1));

  assertEquals("Test longer value", 4094, htoi("FFe", 3));

  return 0;
}
