#include "stringutils.h"
#include "stdlib.h"
#include "stdio.h"

#define MAX_LEN 2

int main() {
    int len = 0;
    char* line = NULL;
    
    while ((len = readline(&line)) > 0) {
        if (len <= MAX_LEN) {
            printf("%s", line);
            free(line);
            continue;
        }
        

        int cur = 0;
        while (cur < len - 1) {
            char* str = trim(substring(line, cur, cur + MAX_LEN));
            if (!isBlank(str)) {
                printf("%s\n", str);        
            }

            cur += MAX_LEN;
        }
    }

    return 0;
}
