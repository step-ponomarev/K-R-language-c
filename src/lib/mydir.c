#include "mydir.h"
#include "unistd.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>

struct MY_DIR {
  int fd;
  Dirent d;
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

  long esleep = 0;
  char buf[1024];
  int bytes = syscall(SYS_getdirentries64, dir->fd, buf, sizeof(buf), &esleep);
  if (bytes < 0) {
    printf("ERRROR\n");
    return NULL;
  }

  int offset = 0;
  Dirent *dirent;
  while ((dirent = (Dirent *)(buf + offset))->d_reclen > 1) {
    printf("Name: %.*s\n", dirent->d_namlen, dirent->d_name);
    offset += dirent->d_reclen;
  }

  return NULL;
}

void my_closedir(MY_DIR *dir) {
  if (dir == NULL) {
    return;
  }

  syscall(SYS_close, dir->fd);
  free(dir);
}

int main(const int argc, const char *argv[]) {
  MY_DIR *not_null_dir = my_opendir("src");
  my_readdir(not_null_dir);

  return 0;
}
