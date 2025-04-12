#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

/*
deprecated
*/

void copyWithSize(char from[], char to[], int size);
void expandArray(char**arr, int currSize, int newSize);
int readline(char** line);
char isSymbol(int ch);
char isEmpty(int ch);
/*
    [startIndex, endIndex)
*/
char* substring(char* line, int startIndex, int endIndex);
char* trim(char* line);
char isBlank(char* line);
void reverse(char str[]);

#endif