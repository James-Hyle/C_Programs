#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ProcEntry.h"


int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Usage: %s <stat file path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *argcpy = strdup(argv[1]);

    ProcEntry *p = CreateProcEntryFromFile(argcpy);

    char *p_string = ProcEntryToString(p);

    printf("%s\n", p_string);

    free(p_string);
    free(argcpy); // added free for mem safety
    DestroyProcEntry(p);

    return 0;
}