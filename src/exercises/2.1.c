#include "float.h"
#include "limits.h"
#include "stdio.h"

void printByLibConsts();
void printByHand();
void printCharLimits();
void printIntLimits();
void printLongIntLimits();
void printFloadLimits();

int main() {
  printByLibConsts();
  printByHand();

  return 0;
}

void printByHand() {
  printf("-------------------------\n");
  printf("PRINT LIMITS BY HAND");
  printf("-------------------------\n");

  printCharLimits();
  printIntLimits();
  printLongIntLimits();
}

void printFloadLimits() {
  float i = 1;
  // printf("%f\n", );
}

void printLongIntLimits() {
  printf("Signed long int limits\n");

  unsigned long int uMax = 0 - 1;

  long int max = (uMax >> 1);
  printf("Min value: %ld\n", max + 1);
  printf("Max value: %ld\n", max);
  printf("-------------------------\n");

  printf("Unsigned long int limits\n");
  printf("Max value: %lu\n", uMax);
  printf("-------------------------\n");
}

void printIntLimits() {
  printf("Signed int limits\n");

  unsigned int maxUint = ~0;

  int max = (maxUint >> 1);
  printf("Min value: %d\n", max + 1);
  printf("Max value: %d\n", max);
  printf("-------------------------\n");

  printf("Unsigned int limits\n");
  printf("Max value: %ud\n", maxUint);
  printf("-------------------------\n");
}

void printCharLimits() {
  printf("Signed char limits\n");
  unsigned char uMax = 0 - 1;

  char max = (uMax >> 1);
  printf("Min value: %hhd\n", max + 1);
  printf("Max value: %hhd\n", max);
  printf("-------------------------\n");

  printf("Unsigned char limits\n");
  printf("Max value: %u\n", uMax);
  printf("-------------------------\n");
}

void printByLibConsts() {
  printf("-------------------------\n");
  printf("PRINT LIMITS BY CONSTANTS");
  printf("-------------------------\n");
  printf("Signed char limits\n");
  printf("Min value: %d\n", CHAR_MIN);
  printf("Max value: %d\n", CHAR_MAX);
  printf("-------------------------\n");

  printf("Unsigned char limits\n");
  printf("Max value: %d\n", UCHAR_MAX);
  printf("-------------------------\n");

  printf("Signed short limits\n");
  printf("Min value: %d\n", SHRT_MIN);
  printf("Max value: %d\n", SHRT_MAX);
  printf("-------------------------\n");

  printf("Unsigned short limits\n");
  printf("Max value: %d\n", USHRT_MAX);
  printf("-------------------------\n");

  printf("Signed int limits\n");
  printf("Min value: %d\n", INT_MAX);
  printf("Max value: %d\n", INT_MAX);
  printf("-------------------------\n");

  printf("Unsigned int limits\n");
  printf("Max value: %d\n", UINT_MAX);
  printf("-------------------------\n");

  printf("Signed long limits\n");
  printf("Min value: %ld\n", LONG_MIN);
  printf("Max value: %ld\n", LONG_MAX);
  printf("-------------------------\n");

  printf("Signed long long limits\n");
  printf("Min value: %lld\n", LONG_LONG_MIN);
  printf("Max value: %lld\n", LONG_LONG_MAX);
  printf("-------------------------\n");

  printf("Unsigned long limits\n");
  printf("Max value: %lu\n", ULONG_MAX);
  printf("Max unsigned long long value: %llu\n", ULONG_LONG_MAX);
  printf("-------------------------\n");

  printf("Float limitd\n");
  printf("Max value: %f\n", FLT_MAX);
  printf("Min value: %f\n", FLT_MAX + 1);
}
