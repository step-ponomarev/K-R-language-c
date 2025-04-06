#include "stringutils.h"
#include "stdio.h"

int main() {
    char * line = NULL;
    int size = 0;

    while ((size = getlineImpl(&line)) && size > 0) {
        reverse(line);
        printf("%s", line);
    }

    return 0;
}