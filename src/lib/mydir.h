#ifndef MYDIR_H_
#define MYDIR_H_

#include <sys/dirent.h>
typedef struct dirent Dirent;
typedef struct MY_DIR MY_DIR;

MY_DIR *my_opendir(const char *);
Dirent *my_readdir(MY_DIR *);
void my_closedir(MY_DIR *);

#endif
