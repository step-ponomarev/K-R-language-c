#include "stringutils.h"
#include <stdio.h>
#include <stdlib.h>

#define TAB_LEN 4

char* detab(char* line);

int main() {
    char * line = NULL;
    int len = 0;

    while ((len = readline(&line)) > 0) {
        char * detabedLine = detab(line);
        printf("%s", detabedLine);
        if (line != detabedLine) {
            free(detabedLine);
        }
        free(line);
    }

    return 0;
}

char* detab(char* line) {
    int len = 0;
    int tabCount = 0;
    while (line[len] != '\0') {
        if (line[len] == '\t') {
            tabCount++;
        }
        len++;
    }

    if (tabCount == 0) {
        return line;
    }

    int newLen = len + (tabCount * TAB_LEN) - tabCount;
    char* detabedLine = malloc(sizeof(char) * newLen);
    
    int i = newLen - 1;
    while (len >= 0) {
        if (line[len] == '\t') {
            for (int j = 0; j < TAB_LEN - 1; j++) {
                detabedLine[i--] = ' ';
            }
        } else {
            detabedLine[i] = line[len];
            i--;
        }

        len--;
    }

    return detabedLine;
}
