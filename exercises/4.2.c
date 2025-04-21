#include "../lib/asserts.h"
#include "../lib/char_utils.h"
#include "stdio.h"

double atof(char s[]) {
  int i = 0;
  for (int i = 0; s[i] == '\t' || s[i] == ' '; i++) {
  }
  const short int sign = s[i] == '-' ? -1 : 1;
  while (!isDigit(s[i])) {
    i++;
  }

  double val = 0.0;
  while (isDigit(s[i])) {
    val = 10.0 * val + (s[i++] - '0');
  }

  if (s[i] == '.') {
    i++;
  }

  double pow = 1.0;
  while (isDigit(s[i])) {
    val = 10.0 * val + (s[i++] - '0');
    pow *= 10.0;
  }

  if (s[i] == '\0') {
    return sign * val / pow;
  }

  // skip e/E
  i++;

  const char isNegativeExp = s[i] == '-';
  if (isNegativeExp) {
    i++;
  }

  int expCount = 0;
  while (isDigit(s[i])) {
    expCount = expCount * 10 + (s[i++] - '0');
  }

  double exp = 1.0;
  for (int i = 0; i < expCount; i++) {
    exp *= 10.0;
  }

  double res = (sign * val / pow);
  if (isNegativeExp) {
    return res / exp;
  }

  return res * exp;
}

int main() {
  assertEquals("Test 1.1", 1.1, atof("1.1"));
  assertEquals("Test 0", 0.0, atof("0"));
  assertEquals("Test -1.22", -1.22, atof("-1.22"));
  assertEquals("Test -1.22e3", -1220.0, atof("-1.22e3"));
  assertEquals("Test 1.22e-1", 0.122, atof("1.22e-1"));

  return 0;
}
