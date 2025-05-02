#ifndef CHAR_UTILS_H_
#define CHAR_UTILS_H_

char isEmpty(char);
char isDigit(char);
char isEquals(const char[], const char[]);
int lengthOf(char[]);
int copy_string(const char src[], char **dest);

int string_compare(const char *, const char *);
int string_compare_ignore_register(const char *, const char *);

char *substring(char *line, int startIndex, int endIndex);
char *trim(char *line);
char isBlank(char *line);
void reverse(char *str);

#endif
