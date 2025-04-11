#ifndef STRING_H_
#define STRING_H_

struct String {
    char * str;
    int length;
};

struct String createString(char * ch);
void destroyString(struct String string);

#endif