#include "buffered_reader.h"
#include "queue.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum boolean { TRUE = 1, FALSE = 0 } boolean;

#define MAX_READ_LINE 256

struct BufferedReader {
  Queue *queue;
  boolean eof;
};

char is_need_fill_buffer(const BufferedReader *);
void fill_buffer(BufferedReader *);
size_t reader_size(const BufferedReader *);

BufferedReader *buffered_reader_create() {
  BufferedReader *reader = malloc(sizeof(BufferedReader));
  reader->queue = queue_create(sizeof(int));
  reader->eof = FALSE;

  return reader;
}
void buffered_reader_destroy(BufferedReader *reader) {
  queue_destroy(reader->queue);
  free(reader);
}

int buffered_reader_get_char(BufferedReader *reader) {
  fill_buffer(reader);
  if (reader_size(reader) == 0 || reader->eof) {
    return EOF;
  }

  int res;
  queue_poll(reader->queue, &res);

  return res;
}

void buffered_reader_unget_char(BufferedReader *reader, const int ch) {
  queue_add_at_start(reader->queue, &ch);
}

void buffered_reader_get_line(BufferedReader *reader, char **dest) {
  fill_buffer(reader);
  if (reader_size(reader) == 0 || reader->eof) {
    return;
  }

  Queue *line = queue_create(sizeof(char));

  int ch;
  do {
    ch = buffered_reader_get_char(reader);
    if (ch == EOF || ch == '\0') {
      break;
    }
    queue_add(line, &ch);

    if (ch == '\n') {
      break;
    }
  } while (reader_size(reader) > 0);

  const int end = '\0';
  queue_add(line, &end);

  const int size = queue_size(line);
  char *newLine = malloc(sizeof(char) * size);
  for (int i = 0; i < size; i++) {
    queue_poll(line, &newLine[i]);
  }

  *dest = newLine;
  queue_destroy(line);
}

void buffered_reader_unget_string(const BufferedReader *reader,
                                  const char *str) {
  int i = 0;
  while (str[i++] != '\0') {
  }
  i--;

  while (str[i] >= 0) {
    queue_add_at_start(reader->queue, &str[i--]);
  }
}

void fill_buffer(BufferedReader *reader) {
  if (!is_need_fill_buffer(reader)) {
    return;
  }

  int ch;
  do {
    ch = getchar();
    queue_add(reader->queue, &ch);
    if (ch == EOF) {
      reader->eof = TRUE;
    }
  } while (ch != EOF && ch != '\n');
}

char is_need_fill_buffer(const BufferedReader *reader) {
  if (reader->eof) {
    return 0;
  }

  return reader_size(reader) == 0;
}

size_t reader_size(const BufferedReader *reader) {
  return queue_size(reader->queue);
}
