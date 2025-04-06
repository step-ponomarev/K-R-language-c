#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

void copyWithSize(char from[], char to[], int size);
void expandArray(char **arr, int currSize, int newSize);
int getlineImpl(char **line);

#endif