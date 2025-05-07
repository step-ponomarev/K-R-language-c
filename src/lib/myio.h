#ifndef MY_IO_H_
#define MY_IO_H_

// https://github.com/apple-oss-distributions/xnu/blob/main/bsd/kern/syscalls.master
// https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md
// man 2 syscall_num

typedef struct MY_FILE MY_FILE;

#undef EOF
#define EOF -1

extern MY_FILE *__myin;
extern MY_FILE *__myout;
extern MY_FILE *__myerr;

#define myin __myin
#define myout __myout
#define myerr __myerr

// r,w, r+w
MY_FILE *my_open(const char *, const char *);
int my_getc(MY_FILE *);
int my_putc(MY_FILE *, char);
void my_ungetc(MY_FILE *, char);

#endif
