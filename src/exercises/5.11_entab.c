
#include <stdio.h>
#include <stdlib.h>

#define READ_BUFFER_SIZE 1000
#define TAB_SIZE 4
#define STANDART_TABS_LEN 5
static const int STANDART_TAB_POS[STANDART_TABS_LEN] = {4, 8, 12, 16, 20};

int main(int argc, char *argv[]) {
  const char useStandartArgs = argc == 1;
  const int tabPosLen = useStandartArgs ? STANDART_TABS_LEN : argc - 1;
  int tabPos[tabPosLen];

  if (useStandartArgs) {
    for (int i = 0; i < STANDART_TABS_LEN; i++) {
      tabPos[i] = STANDART_TAB_POS[i];
    }
  } else {
    for (int i = 1; i < argc; i++) {
      tabPos[i - 1] = atoi(argv[i]);
    }
  }

  char buffer[READ_BUFFER_SIZE];
  int curTabPosIndex = 0;
  int curPos = 0;

  int ch;
  while ((ch = getchar()) != EOF && curPos < READ_BUFFER_SIZE) {
    if (curPos > tabPos[curTabPosIndex] && curTabPosIndex < (tabPosLen - 1)) {
      curTabPosIndex++;
    }

    int spaceCount = ch == ' ';
    while ((ch = getchar()) == ' ' && curPos < tabPos[curTabPosIndex]) {
      spaceCount++;

      if (spaceCount == TAB_SIZE) {
        if (curPos > tabPos[curTabPosIndex] &&
            curTabPosIndex < (tabPosLen - 1)) {
          curTabPosIndex++;
        }

        buffer[curPos++] = '\t';
        spaceCount = 0;
      }
    }

    for (int i = 0; i < spaceCount; i++) {
      buffer[curPos++] = ' ';
    }

    buffer[curPos++] = ch;
  }

  buffer[curPos++] = '\0';

  printf("replaced space: %s\n", buffer);

  return 0;
}
