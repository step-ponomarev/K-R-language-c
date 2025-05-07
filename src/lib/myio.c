#include "myio.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>

// https://github.com/apple-oss-distributions/xnu/blob/main/bsd/kern/syscalls.master

#define FULL_PERMISSIONS 0666
#define FILE_LIMIT 20
#define BLOCK_SIZE 1024

struct MY_FILE {
  int fd;
  int aid;
  char *buf;
  int buffer_pos;
  int buffer_size;
  int flags;
};

static MY_FILE OPPENED_FILES[FILE_LIMIT] = {
    {.fd = 0, .aid = 0, .buf = NULL, .buffer_size = 0, .flags = O_RDONLY},
    {.fd = 1, .aid = 1, .buf = NULL, .buffer_size = 0, .flags = O_WRONLY},
    {.fd = 2, .aid = 2, .buf = NULL, .buffer_size = 0, .flags = O_WRONLY}};
static size_t CURR_AID = 3;

MY_FILE *__myin = &OPPENED_FILES[0];
MY_FILE *__myout = &OPPENED_FILES[1];
MY_FILE *__myerr = &OPPENED_FILES[2];

int parse_flags(const char *);
int _fill_buff(MY_FILE *);

MY_FILE *my_open(const char *path, const char *fp) {
  const int flags = parse_flags(fp);
  if (flags == -1) {
    return NULL;
  }

  const int fd = syscall(SYS_open, path, flags, FULL_PERMISSIONS);
  if (fd < 0) {
    return NULL;
  }

  OPPENED_FILES[CURR_AID] = (MY_FILE){
      .fd = fd, .aid = CURR_AID, .buf = NULL, .buffer_size = 0, .flags = flags};

  return &OPPENED_FILES[CURR_AID++];
}

int my_getc(MY_FILE *file) {
  if (file == NULL || (file->buffer_pos < 0)) {
    return EOF;
  }

  if (file->buf == NULL || file->buffer_pos == file->buffer_size) {
    _fill_buff(file);
  }

  return file->buffer_pos < 0 ? EOF : file->buf[file->buffer_pos++];
}

int _fill_buff(MY_FILE *file) {
  if (file->buffer_pos < 0) {
    return 0;
  }

  char buffer[BLOCK_SIZE];
  const int read_size = syscall(SYS_read, file->fd, buffer, BLOCK_SIZE);
  if (read_size < 0) {
    return read_size;
  }

  // EOF
  if (read_size == 0) {
    file->buffer_pos = -1;
    return 0;
  }

  const size_t byte_size = sizeof(char) * read_size;
  if (file->buf == NULL) {
    // TODO: malloc -> brk
    file->buf = malloc(byte_size);
  } else {
    // TODO: malloc -> brk
    file->buf = realloc(file->buf, byte_size);
  }
  memcpy(file->buf, buffer, read_size);

  file->buffer_size = read_size;
  file->buffer_pos = 0;

  return read_size;
}

int main() {
  int ch;
  while ((ch = my_getc(myin)) != EOF) {
    printf("%c", ch);
  }

  return 0;
}

// r/w/r+w/w+r/
// returns -1 if combination is unsupported
int parse_flags(const char *flags) {
  if (*flags != 'r' && *flags != 'w') {
    return -1;
  }

  if (flags[1] == '\0') {
    return *flags == 'r' ? O_RDONLY : O_WRONLY;
  }

  if (flags[1] != '+') {
    return -1;
  }

  if (flags[2] != 'r' && flags[2] != 'w') {
    return -1;
  }

  return O_RDWR;
}
