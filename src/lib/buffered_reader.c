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

int buffered_reader_get_line(BufferedReader *reader, char *dest,
                             const size_t limit) {
  fill_buffer(reader);
  if (reader_size(reader) == 0 || reader->eof) {
    return 0;
  }

  if (limit == 0) {
    return 0;
  }

  Queue *line = queue_create(sizeof(char));

  int ch;
  do {
    ch = buffered_reader_get_char(reader);
    if (ch == EOF || ch == '\0' || ch == '\n') {
      break;
    }

    queue_add(line, &ch);
  } while (reader_size(reader) > 0 && queue_size(line) < limit - 1);

  if (queue_is_empty(line)) {
    queue_destroy(line);
    return 0;
  }

  const int end = '\0';
  queue_add(line, &end);

  const int size = queue_size(line);
  for (int i = 0; i < size; i++) {
    queue_poll(line, &dest[i]);
  }
  queue_destroy(line);

  return size;
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

char buffered_reader_is_eof(const BufferedReader *reader) {
  return reader->eof && queue_size(reader->queue) <= 1;
}

void fill_buffer(BufferedReader *reader) {
  if (!is_need_fill_buffer(reader)) {
    return;
  }

  int ch;
  do {
    ch = getchar();
    if (ch == EOF) {
      reader->eof = TRUE;
    } else {
      queue_add(reader->queue, &ch);
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
