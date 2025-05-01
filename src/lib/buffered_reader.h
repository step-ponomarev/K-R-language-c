#ifndef BUFFERED_READER_H_
#define BUFFERED_READER_H_

#include <stddef.h>
typedef struct BufferedReader BufferedReader;

BufferedReader *buffered_reader_create();
void buffered_reader_destroy(BufferedReader *);

int buffered_reader_get_char(BufferedReader *);
void buffered_reader_unget_char(BufferedReader *, const int);

int buffered_reader_get_line(BufferedReader *, char *, const size_t);
void buffered_reader_unget_string(const BufferedReader *, const char *);

char buffered_reader_is_eof(const BufferedReader *);

#endif
