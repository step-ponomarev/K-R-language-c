#include "stdio.h"
#include "stringutils.h"

#define LONG_LINE_LENGTH 80

int main() {
    char * line = NULL;
    int len = 0;
    while ((len = readline(&line)) > 0) {
        if (len > LONG_LINE_LENGTH) {
            printf("%s", line);
        }
    }

    return 0;
}