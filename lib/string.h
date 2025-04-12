#ifndef STRING_H_
#define STRING_H_

struct String {
    char * str;
    int length;
};

struct String createString(char*);
void destroyString(struct String);
struct String trim(struct String);

/*
string from to,
 */
struct String substring(struct String, int, int);

#endif