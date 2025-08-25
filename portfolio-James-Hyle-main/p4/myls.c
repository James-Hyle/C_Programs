#define _POSIX_C_SOURCE 2
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "file-info.h"

void printUsage(char *s) {
    printf("Usage: %s -d <directory> [-t/s] [-D]\n", s);
    printf("\t-d <dir> Specify directory.\n");
    printf("\t-s       Sort by file size.\n");
    printf("\t-t       Sort by last modified time.\n");
    printf("\t-D       Only output directories, exclude regular files.\n");
}

int main(int argc, char **argv) {

    char *path = NULL;
    int opt = 0;

    ListPtr list;
    FileInfo *file;

    bool useTimeSort = false;
    bool useSizeSort = false;
    bool showDirectoriesOnly = false;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory> <flags>\n", argv[0]);
        return 1;
    }

    // Read in command line args with getopt
    while ((opt = getopt(argc, argv, "tsDd:")) != -1) {
        switch (opt) {

        case 'd':
            path = strdup(optarg);
            break;

        case 's':
            useSizeSort = true;
            break;

        case 't':
            useTimeSort = true;
            break;

        case 'D':
            showDirectoriesOnly = true;
            break;

        default:
            printUsage(argv[0]);
            return 1;
        }
    }

    if (path == NULL) {
        printUsage(path);
        exit(1);
    }

    // Create list with default compar
    list = CreateList(FileInfoCompareTypeAndName, FileInfoToString, DestroyFileInfo);

    if (useSizeSort) { list->Compar = FileInfoCompareSize; }

    if (useTimeSort) { list->Compar = FileInfoCompareTime; }

    // Open directory according to path
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        exit(1);
    }

    // Change process environment to directory according to path
    chdir(path);

    struct dirent *entry;
    struct stat buff;
    int status;

    while ((entry = readdir(dir)) != NULL) {

        status = lstat(entry->d_name, &buff);
        if (status == -1) {
            perror("Error getting file stats");
            exit(1);
        }

        file = CreateFileInfo(entry->d_name, buff.st_mtime, buff.st_size, buff.st_mode);
        if (file == NULL) {
            perror("Error creating FileInfo");
            exit(1);
        }
        
        // Add validated entry to list
        ListAppend(list, file);
    }
    // Cleanup
    closedir(dir);
    free(path);

    // Sort list according to compar
    ListSort(list);

    // Print list according to if -D flag set
    if (showDirectoriesOnly) { 
        ListPrint(list, FileInfoDirFilter);
    } else { 
        ListPrint(list, FileInfoNoFilter);
    }

    // Little more cleanup
    DestroyList(list);
    return 0;
}
