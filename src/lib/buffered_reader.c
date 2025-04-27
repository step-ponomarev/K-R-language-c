#include "buffered_reader.h"
#include <stddef.h>

#define BUFFER_SIZE 256

struct BufferedReader {
  int *buffer;
  size_t curr_size;
  size_t curr_pos;
};
