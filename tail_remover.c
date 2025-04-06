#include "stdio.h"
#include <stdlib.h> 
#include "stringutils.h"

int main() {
    char *currLine = NULL;
    int currLen;

    while((currLen = getlineImpl(&currLine)) > 0) {
        for (int i = currLen - 2; i >= 0; i--) {
            if ((i > 0) && !isSymbol(currLine[i])) {
                continue;
            }

            if (isSymbol(currLine[i])) {
                currLine[i + 1] = '\n';
                currLine[i + 2] = '\0';
            } else {
                currLine[i] = '\n';
                currLine[i + 1] = '\0';
            }

            break;
        }

        printf("%s", currLine);
    }

    return 0;
}