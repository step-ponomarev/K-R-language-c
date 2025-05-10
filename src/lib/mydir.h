#ifndef MYDIR_H_
#define MYDIR_H_

#include <stddef.h>
#include <sys/dirent.h>
#include <sys/stat.h>

typedef struct dirent Dirent;
typedef struct stat Stat;
typedef struct MY_DIR MY_DIR;

MY_DIR *my_opendir(const char *);
// returns dir entity info next on each call
Dirent *my_readdir(MY_DIR *);
size_t my_fsize(const char *);
void my_closedir(MY_DIR *);

#endif
