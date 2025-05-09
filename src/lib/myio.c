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

#define MY_O_RDONLY O_RDONLY
#define MY_O_WRONLY O_WRONLY
#define MY_O_RDWR O_RDWR
#define MY_O_CREAT O_CREAT
#define MY_O_TRUNC O_TRUNC
#define MY_O_APPEND 0b01000
#define MY_O_UNBUFF 0b10000

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
    {.fd = 0, .aid = 0, .rb = NULL, .wb = NULL, .fo = 0, .flags = MY_O_RDONLY},
    {.fd = 1,
     .aid = 1,
     .rb = NULL,
     .wb = NULL,
     .fo = 0,
     .flags = MY_O_WRONLY | MY_O_UNBUFF},
    {.fd = 2,
     .aid = 2,
     .rb = NULL,
     .wb = NULL,
     .fo = 0,
     .flags = MY_O_WRONLY | MY_O_UNBUFF}};

static size_t CURR_AID = 3;

MY_FILE *__myin = &OPPENED_FILES[0];
MY_FILE *__myout = &OPPENED_FILES[1];
MY_FILE *__myerr = &OPPENED_FILES[2];

int _parse_flags(const char *);
int _fill_buff(const int, _buf *);
int _flush_buff(const int, _buf *);
int _prev_block(MY_FILE *);
void _destroy_file(MY_FILE *);
void _destroy_buf(_buf *);

MY_FILE *my_open(const char *path, const char *fp) {
  const int flags = _parse_flags(fp);
  if (flags == -1) {
    return NULL;
  }

  const int fd = syscall(SYS_open, path, flags, FULL_PERMISSIONS);
  if (fd < 0) {
    return NULL;
  }

  if (flags & MY_O_APPEND && (syscall(SYS_lseek, fd, 0, SEEK_END) < 0)) {
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

int my_close(MY_FILE *file) {
  if (file == NULL) {
    return -1;
  }

  if (file->wb != NULL) {
    my_flush(file);
  }

  _destroy_file(file);
  for (int i = file->aid + 1; i < CURR_AID; i++) {
    OPPENED_FILES[i - 1] = OPPENED_FILES[i];
    OPPENED_FILES[i].aid = i - 1;
  }
  CURR_AID--;

  return 0;
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

int my_putc(MY_FILE *file, char ch) {
  if (file == NULL || !(file->flags & O_WRONLY) && !(file->flags & O_RDWR)) {
    return -1;
  }

  const char unbuff = (file->flags & MY_O_UNBUFF) != 0;
  if (file->wb == NULL) {
    file->wb = malloc(sizeof(_buf));
    file->wb->s = unbuff ? 1 : BLOCK_SIZE;
    file->wb->buf = malloc(sizeof(char) * file->wb->s);
    file->wb->p = 0;
  }

  file->wb->buf[file->wb->p++] = ch;
  if (file->wb->p == file->wb->s && (_flush_buff(file->fd, file->wb) < 0)) {
    return -1;
  }

  return 0;
}

int my_ungetc(MY_FILE *file, char ch) {
  if (file == NULL || file->rb == NULL || (file->flags & MY_O_UNBUFF)) {
    return -1;
  }

  if (file->rb->p != 0) {
    file->rb->buf[--(file->rb->p)] = ch;
    return 0;
  }

  if ((file->fo != 0) && (_prev_block(file) < 0)) {
    return -1;
  }

  file->rb->p = file->rb->s;
  file->rb->buf[--(file->rb->p)] = ch;

  return 0;
}

int my_flush(MY_FILE *file) {
  if (file == NULL ||
      !(file->flags & MY_O_RDWR) && !(file->flags & MY_O_WRONLY)) {
    return -1;
  }

  return file->wb == NULL ? 0 : _flush_buff(file->fd, file->wb);
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
  }
  memcpy(buf->buf, buffer, read_size);

  buf->s = read_size;
  buf->p = 0;

  return read_size;
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

  buf->p = 0;

  return 0;
}

// r/w/r+w/w+r/a
// returns -1 if combination is unsupported
int _parse_flags(const char *flags) {
  int fl = 0;
  while (*flags != '\0') {
    if (*flags == '+') {
      continue;
      flags++;
    }

    if (*flags == 'w') {
      fl |= MY_O_RDWR | MY_O_CREAT | MY_O_TRUNC;
    }

    if (*flags == 'r') {
      fl |= MY_O_RDONLY;
    }

    if (*flags == 'a') {
      fl |= MY_O_APPEND | MY_O_RDWR;
    }

    flags++;
  }

  return fl;
}

void _destroy_file(MY_FILE *file) {
  if (file == NULL) {
    return;
  }

  _destroy_buf(file->rb);
  _destroy_buf(file->wb);
}

void _destroy_buf(_buf *buf) {
  if (buf == NULL) {
    return;
  }

  if (buf->buf != NULL) {
    free(buf->buf);
  }

  free(buf);
}

int main() {
  MY_FILE *f = my_open("test.txt", "a:w");

  my_putc(f, '3');
  my_putc(f, '\n');

  my_close(f);

  return 0;
}
