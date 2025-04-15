#include "../../lib/iolib.h"
#include "stdio.h"

#define INCLUDE "#include"
#define COMMENT_LINE "//"
#define COMMENT_MULTILINE_START "/*"

/*
    Упражнение 1.24. Напишите программу, проверяющую Си-программы
    на элементарные синтаксические ошибки вроде несбалансированности
    скобок всех видов. Не забудьте о кавычках (одиночных и двойных),
    эскейп-последовательностях (\. . . ) и комментариях. (Это сложная
    программа, если писать ее для общего случая.)
*/

int main() {
  String word;
  while ((word = readWord()).length > 0) {
    printf("%s\n", word);
  }

  return 0;
}
