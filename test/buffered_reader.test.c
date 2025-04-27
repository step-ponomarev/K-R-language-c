#include "../src/lib/buffered_reader.h"
#include <stdio.h>

int main() {
  BufferedReader *reader = buffered_reader_create();

  buffered_reader_unget_char(reader, EOF);
  buffered_reader_unget_string(reader, "It's the end\n");
  int e;
  while ((e = buffered_reader_get_char(reader)) != EOF) {
    printf("%c", e);
  }

  buffered_reader_destroy(reader);
}
