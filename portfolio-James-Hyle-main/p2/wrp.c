#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int length = atoi(argv[1]);

    if (length <= 0) {
        fprintf(stderr, "Error: Length must be a positive integer.\n");
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;

    while ((linelen = getline(&line, &linecap, stdin)) != -1) {
        int i = 0;
        int count = 0;
        int word_start = 0;

        // iterate over read line
        while (i < linelen) {
            while (i < linelen && line[i] == ' ') {
                i++;
            }
            // get start of word in buffer
            word_start = i;

            // read until newline
            while (i < linelen && line[i] != ' ' && line[i] != '\n') {
                i++;
            }

            // get word length for calculations
            int word_length = i - word_start;


            // space or newline
            if (word_length == 0) {
                break;
            }

            // calculate if word length will exceed column length
            if (count + word_length + (count > 0 ? 1 : 0) > length) {
                putchar('\n');
                count = 0;
            }

            if (count > 0) {
                putchar(' ');
                count++;
            }

            for (int j = word_start; j < i; j++) {
                putchar(line[j]);
            }
            count += word_length;
        }

        putchar('\n');
    }

    free(line);
    return 0;
}