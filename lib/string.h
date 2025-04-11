#ifndef STRING_H_
#define STRING_H_

struct String {
    char * str;
    int len;
    void * ref;
};

struct String* toString(char * ch);
void destroy(struct String* string);

#endif