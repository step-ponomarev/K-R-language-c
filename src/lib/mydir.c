#include "mydir.h"
#include "unistd.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>

typedef struct _derent_buf {
  Dirent d;
  char buf[1024];
  int bytes;
  int offset;
} _dirent_buf;

struct MY_DIR {
  int fd;
  _dirent_buf *dirent;
};

MY_DIR *my_opendir(const char *path) {
  if (path == NULL) {
    return NULL;
  }

  struct stat stat;
  if ((syscall(SYS_stat, path, &stat) < 0) || (stat.st_mode & S_IFDIR) == 0) {
    return NULL;
  }

  const int fd = syscall(SYS_open, path, O_RDONLY, 0);
  if (fd < 0) {
    return NULL;
  }

  MY_DIR *dir = malloc(sizeof(MY_DIR));
  if (dir == NULL) {
    return NULL;
  }
  dir->fd = fd;

  return dir;
}

Dirent *my_readdir(MY_DIR *dir) {
  if (dir == NULL) {
    return NULL;
  }

  if (dir->dirent == NULL) {
    dir->dirent = malloc(sizeof(_dirent_buf));
  }

  if (dir->dirent->bytes <= 0) {
    long esleep = 0;
    dir->dirent->bytes = syscall(SYS_getdirentries64, dir->fd, dir->dirent->buf,
                                 sizeof(dir->dirent->buf), &esleep);
  }

  _dirent_buf *dirent = dir->dirent;
  if (dirent->bytes <= 0) {
    return NULL;
  }

  if ((dirent->d = *((Dirent *)(dirent->buf + dirent->offset))).d_reclen <= 1) {
    dir->dirent = NULL;
    free(dirent); // if end go to start
    return NULL;
  }
  dirent->offset += dirent->d.d_reclen;

  return &dirent->d;
}

void my_closedir(MY_DIR *dir) {
  if (dir == NULL) {
    return;
  }

  syscall(SYS_close, dir->fd);
  if (dir->dirent != NULL) {
    free(dir->dirent);
  }
  free(dir);
}
