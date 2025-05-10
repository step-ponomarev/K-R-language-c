#include "mydir.h"
#include "unistd.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>

typedef struct _derent_buf {
  Dirent d;
  char buf[1024];
  int bytes;
  int offset;
} _dirent_buf;

typedef struct _dir_name {
  char *n;
  size_t s;
} _dir_name;

struct MY_DIR {
  int fd;
  _dir_name n;
  _dirent_buf *dirent;
};

// 1, 0, -1 if error
char _is_dir(const char *);
char _is_stat_of_dir(const Stat *);

MY_DIR *my_opendir(const char *path) {
  if (path == NULL) {
    return NULL;
  }

  Stat stat;
  if ((syscall(SYS_stat64, path, &stat) < 0) || !_is_stat_of_dir(&stat)) {
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
  dir->n.s = strlen(path);
  dir->n.n = malloc(dir->n.s + 1);
  strcpy(dir->n.n, path);
  dir->n.n[dir->n.s] = '\0';

  return dir;
}

Dirent *my_readdir(MY_DIR *dir) {
  if (dir == NULL) {
    return NULL;
  }

  if (dir->dirent == NULL) {
    dir->dirent = malloc(sizeof(_dirent_buf));
    long _ = 0;
    dir->dirent->bytes = syscall(SYS_getdirentries64, dir->fd, dir->dirent->buf,
                                 sizeof(dir->dirent->buf), &_);
    dir->dirent->offset = 0;
  }

  _dirent_buf *dirent = dir->dirent;
  if (dirent->bytes <= 0) {
    free(dirent);
    dir->dirent = NULL;
    return NULL;
  }

  if ((dirent->d = *((Dirent *)(dirent->buf + dirent->offset))).d_reclen == 0) {
    free(dir->dirent); // if end go to start
    dir->dirent = NULL;
    return NULL;
  }
  dirent->offset += dirent->d.d_reclen;

  return &dirent->d;
}

size_t my_fsize(const char *path) {
  if (path == NULL) {
    return 0;
  }

  Stat stat;
  if (syscall(SYS_stat64, path, &stat) < 0) {
    return 0;
  }

  if (!_is_stat_of_dir(&stat)) {
    return stat.st_size;
  }

  MY_DIR *dir = my_opendir(path);
  if (dir == NULL) {
    return 0;
  }

  const int cur_path_len = strlen(path);

  size_t size = 0;
  Dirent *dirent;
  while ((dirent = my_readdir(dir)) != NULL) {
    if (strcmp(".", dirent->d_name) == 0 || strcmp("..", dirent->d_name) == 0) {
      continue;
    }

    char name[cur_path_len + dirent->d_namlen + 2]; // 2 - for / an '\0';
    strcpy(name, path);
    name[cur_path_len] = '/';
    strcat(name, dirent->d_name);
    name[cur_path_len + dirent->d_namlen + 1] = '\0';

    size += my_fsize(name);
  }

  my_closedir(dir);

  return size;
}

void my_closedir(MY_DIR *dir) {
  if (dir == NULL) {
    return;
  }

  syscall(SYS_close, dir->fd);
  if (dir->dirent != NULL) {
    free(dir->dirent);
  }
  free(dir->n.n);
  free(dir);
}

char _is_dir(const char *path) {
  Stat stat;
  if (syscall(SYS_stat64, path, &stat) < 0) {
    return -1;
  }

  return _is_stat_of_dir(&stat);
}

char _is_stat_of_dir(const Stat *stat) {
  return (stat->st_mode & S_IFDIR) != 0;
}

int main() {
  printf("%u", my_fsize("src"));

  return 0;
}
