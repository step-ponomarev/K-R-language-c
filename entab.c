#include "stringutils.h"
#include <stdio.h>
#include <stdlib.h>

#define TAB_LEN 4

char* entab(char* line);

int main() {
    char * line = NULL;
    int len = 0;

    while ((len = readline(&line)) > 0) {
        char * entabedLine = entab(line);
        printf("%s", entabedLine);
        if (line != entabedLine) {
            free(entabedLine);
        }
        free(line);
    }

    return 0;
}

char* entab(char* line) {
    int len = 0;
    while (line[len] != '\0') {
        len++;
    }

    char* entabedLine = malloc(sizeof(char) * (len + 1));
    
    int i = 0;
    int j = 0;
    while (i < len) {
        if (line[i] != ' ') {
            entabedLine[j++] = line[i++];
            continue;
        }

        int tmpJ = j;
        int spaceCount = 0;
        int tmpI = i;
        while (line[tmpI] == ' ') {
            spaceCount++;
            entabedLine[tmpJ++] = line[tmpI++];
        }

        int tabCount = spaceCount / TAB_LEN;
        if (tabCount == 0) {
            i = tmpI;
            j = tmpJ;
            continue;
        }

        for (int k = 0; k < tabCount; k++) {
            entabedLine[j++] = '\t';
        }

        i = i + (tabCount * TAB_LEN);
    }
   
    return entabedLine;
}
