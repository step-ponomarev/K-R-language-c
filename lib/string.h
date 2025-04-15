#ifndef STRING_H_
#define STRING_H_

typedef struct {
  char *str;
  int length;
} String;

String createString(char *);
void destroyString(String);
String trim(String);

/*
string from to,
 */
String substring(String, int, int);

char isBlank(String);

#endif
