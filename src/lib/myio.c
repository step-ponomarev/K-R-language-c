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

// TODO: допилить отключение буфферизации для sdin/out/err

typedef struct _buf {
  char *buf;
  int p;
  int s;
} _buf;

struct MY_FILE {
  int fd;
  int aid;
  _buf *rb;
  _buf *wb;
  int fo;
  int flags;
};

static MY_FILE OPPENED_FILES[FILE_LIMIT] = {
    {.fd = 0, .aid = 0, .rb = NULL, .wb = NULL, .fo = 0, .flags = O_RDONLY},
    {.fd = 1, .aid = 1, .rb = NULL, .wb = NULL, .fo = 0, .flags = O_WRONLY},
    {.fd = 2, .aid = 2, .rb = NULL, .wb = NULL, .fo = 0, .flags = O_WRONLY}};
static size_t CURR_AID = 3;

MY_FILE *__myin = &OPPENED_FILES[0];
MY_FILE *__myout = &OPPENED_FILES[1];
MY_FILE *__myerr = &OPPENED_FILES[2];

int parse_flags(const char *);
int _fill_buff(const int, _buf *);
int _flush_buff(const int, _buf *);
int _prev_block(MY_FILE *);

MY_FILE *my_open(const char *path, const char *fp) {
  const int flags = parse_flags(fp);
  if (flags == -1) {
    return NULL;
  }

  const int fd = syscall(SYS_open, path, flags, FULL_PERMISSIONS);
  if (fd < 0) {
    return NULL;
  }

  OPPENED_FILES[CURR_AID] = (MY_FILE){.fd = fd,
                                      .aid = CURR_AID,
                                      .rb = NULL,
                                      .wb = NULL,
                                      .fo = 0,
                                      .flags = flags};

  return &OPPENED_FILES[CURR_AID++];
}

int my_getc(MY_FILE *file) {
  if (file == NULL || (file->flags != O_RDONLY) && !(file->flags & O_RDWR)) {
    return EOF;
  }

  if (file->rb == NULL) {
    file->rb = malloc(sizeof(_buf));
  }

  if (file->rb->p == file->rb->s) {
    const int prev_block_size = file->rb->s;
    if (_fill_buff(file->fd, file->rb) < 0) {
      return -1;
    }

    file->fo += prev_block_size;
  }

  if (file->rb->p < 0) {
    return EOF;
  }

  return file->rb->p < 0 ? EOF : file->rb->buf[file->rb->p++];
}

// TODO: как понять когда флашить
// TODO как понять, что есть что флоашить?
int my_putc(MY_FILE *file, char ch) {
  if (file == NULL || !(file->flags & O_WRONLY) && !(file->flags & O_RDWR)) {
    return -1;
  }

  if (file->wb == NULL) {
    file->wb = malloc(sizeof(_buf));
    file->wb->buf = malloc(sizeof(char) * BLOCK_SIZE);
    file->wb->s = BLOCK_SIZE;
    file->wb->p = 0;
  }

  if (file->wb->p == file->wb->s && (_flush_buff(file->fd, file->wb) < 0)) {
    return -1;
  }

  file->wb->buf[file->wb->p++] = ch;

  return 0;
}

int _flush_buff(const int fd, _buf *buf) {
  if (buf == NULL) {
    return -1;
  }

  if (buf->p == 0) {
    return 0;
  }

  if (syscall(SYS_write, fd, buf->buf, buf->p) < 0) {
    return -1;
  }

  buf->s = BLOCK_SIZE;
  buf->p = 0;

  return 0;
}

int _prev_block(MY_FILE *file) {
  const int new_pos = file->fo > BLOCK_SIZE ? file->fo - BLOCK_SIZE : 0;
  int r = syscall(SYS_lseek, file->fd, new_pos, SEEK_SET);
  if (r < 0) {
    return r;
  }
  file->fo = new_pos;

  return _fill_buff(file->fd, file->rb);
}

int _fill_buff(const int fd, _buf *buf) {
  if (buf == NULL) {
    return -1;
  }

  if (buf->p < 0) {
    return 0;
  }

  char buffer[BLOCK_SIZE];
  const int read_size = syscall(SYS_read, fd, buffer, BLOCK_SIZE);
  if (read_size < 0) {
    return read_size;
  }

  // EOF
  if (read_size == 0) {
    if (buf->buf != NULL) {
      free(buf->buf);
    }

    buf->s = 0;
    buf->p = -1;

    return 0;
  }

  const size_t byte_size = sizeof(char) * read_size;
  if (buf->buf == NULL) {
    // TODO: malloc -> brk
    buf->buf = malloc(byte_size);
  } else {
    // TODO: malloc -> brk
    buf->buf = realloc(buf->buf, byte_size);
  }
  memcpy(buf->buf, buffer, read_size);

  buf->s = read_size;
  buf->p = 0;

  return read_size;
}

// r/w/r+w/w+r/
// returns -1 if combination is unsupported
int parse_flags(const char *flags) {
  int fl = 0;
  while (*flags != '\0') {
    if (*flags == '+') {
      continue;
      flags++;
    }

    if (*flags == 'w') {
      fl |= O_RDWR | O_CREAT;
    }

    if (*flags == 'r') {
      fl |= O_RDONLY;
    }
    flags++;
  }

  return fl;
}

void atexitFn() {}

int main() {
  atexit(&atexitFn);
  my_putc(myout, 'h');
  my_putc(myout, '2');

  return 0;
}
