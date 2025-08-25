#include <stdio.h>
#define MAX_LINE 40

// set ch lowercase by setting 6th bit low
char setBit(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        ch = ch | 32;
    }
    return ch;
}

int main(void) {
    char buffer[MAX_LINE] = {};

    while (fgets(buffer, MAX_LINE, stdin) != NULL) {
        for (int i = 0; i < MAX_LINE - 1; i++) {
            if (buffer[i] == ' ') {
                continue;
            }
            buffer[i] = setBit(buffer[i]);          // capitalize char if lowercase
        }
        printf("%s", buffer);
    }
    return 0;
}