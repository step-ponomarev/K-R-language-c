#include "lib/iolib.h"
#include "stdio.h"
#include "stdlib.h"

#define START_COMMENT '/'
#define START_MULTILINE_COMMENT '*'
#define START_STRING '\"'
#define START_SYMBOL '\''

void handleMultilineComment();
void handleSingleLineComment();
int handleLiteralSymbol(char* res, int curr);
int handleStringLiteral(char* res, int curr);

int main() {
    char* res = malloc(sizeof(char) * (80 * 1000));
    int curr = 0;

    int ch;
    while ((ch = getchar()) != EOF) {
        if (ch == START_COMMENT) {
            int tmp = ch;
            if ((ch = getchar()) == EOF) {
                break;
            }

            if (ch == START_MULTILINE_COMMENT) {
                handleMultilineComment();
                continue;
            }

            if (ch == START_COMMENT) {
                handleSingleLineComment();
                res[curr++] = '\n';
                continue;
            }
            
            res[curr++] = tmp;
            res[curr++] = ch;
            continue;
        }

        if (ch == START_STRING) {
            curr = handleStringLiteral(res, curr);
            continue;
        }

        if (ch == START_SYMBOL) {
            curr = handleLiteralSymbol(res, curr);
            continue;
        }

        res[curr++] = ch;
    }

    res[curr++] = '\0';
    printf("%s", res);

    return 0;
}


void handleSingleLineComment() {
    destroyString(
        readline()
    );
}

void handleMultilineComment() {
    int ch;
    while ((ch = getchar()) != EOF) {
        if (ch != START_MULTILINE_COMMENT) {
            continue;
        }

        ch = getchar();
        if (ch == EOF || ch == START_COMMENT) {
            break;
        }
    }
}

int handleLiteralSymbol(char* res, int curr) {
    int ch;
    while ((ch = getchar()) != EOF) {
        res[curr++] = ch;
        if (ch == '\\') {
            res[curr++] = getchar();
            continue;
        }

        if (ch == START_SYMBOL) {
            return curr;
        }
    }

    return curr;
}

int handleStringLiteral(char* res, int curr) {
    int ch;
    while ((ch = getchar()) != EOF) {
        res[curr++] = ch;
        if (ch == '\\') {
            res[curr++] = getchar();
            continue;
        }

        if (ch == START_STRING) {
            return curr;
        }
    }

    return curr;
}