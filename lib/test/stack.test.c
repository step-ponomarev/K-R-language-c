#include "../stack.h"
#include "stdio.h"

void invertValueTest() {
    printf("Invert value test:\n");
    char data[] = "1234567";
    char expected[] = "7654321";
    char actual[8];

    struct Stack sut = createStack();
    for (int i = 0; i < 7; i++) {
        add(&sut, data[i]);
    }

    int i = 0;
    while (!isStackEmpty(sut)) {
        actual[i++] = pop(&sut);
    }
    actual[i] = '\0';
    destroyStack(sut);

    printf("Expected: %s, actual: %s\n", expected, actual);
}

int main() {
    invertValueTest();

    return 0;
}