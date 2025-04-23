#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

void copyWithSize(char from[], char to[], int size);
void expandArray(char **arr, int currSize, int newSize);

/* deprecated @see iolib.h */
int readline(char **line);
char isSymbol(int ch);
char isEmpty(int ch);
/*
    [startIndex, endIndex)
*/

#endif
