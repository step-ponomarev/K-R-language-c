#include "../lib/iolib.h"
#include "../lib/queue.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT_LINE_COUNT 10

typedef struct Token {
  char *str;
  size_t size;
} Token;

int main(int argc, char *argv[]) {
  const int n = argc > 1 ? atoi(argv[1]) : DEFAULT_LINE_COUNT;
  Queue *queue = queue_create(sizeof(Token));

  printf("%d\n", n);

  int len;
  char line[120];
  while ((len = readline(line)) > 0) {
    if (queue_size(queue) == n) {
      Token toRemoval;
      queue_poll(queue, &toRemoval);
      free(toRemoval.str);
    }

    char *cpy = malloc(len + 1);
    memcpy(cpy, line, len + 1);
    queue_add(queue, &((Token){.str = cpy, .size = len + 1}));
  }

  while (!queue_is_empty(queue)) {
    Token str;
    queue_poll(queue, &str);

    printf("%s\n", str.str);
    free(str.str);
  }

  queue_destroy(queue);
}
