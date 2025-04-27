#ifndef BUFFERED_READER_H_
#define BUFFERED_READER_H_

typedef struct BufferedReader BufferedReader;

BufferedReader *buffered_reader_create();
void buffered_reader_destroy(BufferedReader *);

int buffered_reader_get_char(BufferedReader *);
void buffered_reader_unget_char(BufferedReader *, const int);

void buffered_reader_get_line(BufferedReader *, char **);
void buffered_reader_unget_string(const BufferedReader *, const char *);

#endif
