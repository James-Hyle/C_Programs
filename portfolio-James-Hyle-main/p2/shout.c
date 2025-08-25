#include <stdio.h>

#define MAX_LINE 40

// set ch uppercase by setting 6th high
char setBit(char ch) {
    if (ch >= 'a' && ch <= 'z') {
       ch = ch & ~32;
    }
    return ch;
}

int main(void) {
    char buffer[MAX_LINE] = {};

    while (fgets(buffer, MAX_LINE, stdin) != NULL) {
        for (int i = 0; i < MAX_LINE; i++) {
            if (buffer[i] == ' ') { continue; }
            buffer[i] = setBit(buffer[i]);          // capitalize char if lowercase
        }
        printf("%s", buffer);
    }
    return 0;
}