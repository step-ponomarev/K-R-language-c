#include "stdio.h"
#include <stdlib.h> 
#include "stringutils.h"

int main() {
    char *currLine = NULL;
    int currLen;

    int maxLen;
    char *maxLine = NULL;

    while((currLen = getlineImpl(&currLine)) > 0) {
        if (currLen < maxLen) {
            free(currLine);
        } else {
            maxLine = currLine;
            maxLen = currLen;
        }

        currLine = NULL;
    }

    if (maxLine != NULL) {
        printf("%s", maxLine);
    }

    return 0;
}