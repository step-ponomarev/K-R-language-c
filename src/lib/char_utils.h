#ifndef CHAR_UTILS_H_
#define CHAR_UTILS_H_

char isEmpty(char);
char isDigit(char);
char isEquals(const char[], const char[]);
int lengthOf(char[]);

char *substring(char *line, int startIndex, int endIndex);
char *trim(char *line);
char isBlank(char *line);
void reverse(char *str);

#endif
