#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <c>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int i;
    char deleteChar = *argv[1];

    if (deleteChar >= 'a' && deleteChar <= 'z') {
        fprintf(stderr, "Error: Must enter a valid char to delete.\n");
        exit(EXIT_FAILURE);
    }


    while ((linelen = getline(&line, &linecap, stdin)) != -1) {
        i = 0;
        while (i < linelen) {
            if (line[i - 1] == deleteChar && line[i] == deleteChar) {
                i++;
            } else {
                putchar(line[i]);
                i++;
            }
        }
    }
}