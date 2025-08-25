#define _GNU_SOURCE
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
#include <ctype.h>

#include "ProcEntry.h"
#include "List.h"

static char *searchString;

// for filtering
bool ProcEntryMatchCommFilter(const void *entry) {
    // null check
    if (!searchString || !entry)
        return false;

    ProcEntry *e = (ProcEntry *)entry;

    // use strcasestr to match searchString with process comm field
    return (strcasestr(e->comm, searchString) != NULL);
}

// usage statement
void printUsage(void) {
    printf("Usage: ./myps [-s <command>] [-p] [-c] [-z] [-h]\n");
    printf("\t-s <command>  Display proc entries that match command\n");
    printf("\t-p            Display proc entries sorted by pid (default)\n");
    printf("\t-c            Display proc entries sorted by command lexicographically\n");
    printf("\t-z            Display ONLY proc entries in the zombie state\n");
    printf("\t-h            Display this help message\n");
}

int main(int argc, char *argv[]) {

    char *path = NULL;
    int opt = 0;

    ListPtr list;
    ProcEntry *entry;

    bool displayByMatchCOMM = false;
    bool displayByLEX = false;
    bool displayZOMBIES = false;
    bool displayHELP = false;

    if (argc < 2) {
        printUsage();
        return 1;
    }

    // process user arguments for sorting and displaying processes
    while ((opt = getopt(argc, argv, "s:pczh")) != -1) {
        switch (opt) {
        case 's': {
            // wrap optarg with parentheses using asprintf so we can match comm field
            if (asprintf(&searchString, "(%s)", optarg) == -1) {
                perror("asprintf");
                exit(1);
            }
            // debug check state of searchString, we want to wrap with paren so it matches parsed entry->comm
            // printf("%s", searchString);
            displayByMatchCOMM = true;
            break;
        }

        case 'p':
            break;

        case 'c':
            displayByLEX = true;
            break;

        case 'z':
            displayZOMBIES = true;
            break;

        case 'h':
            displayHELP = true;
            break;

        default:
            printUsage();
            return 1;
        }
    }

    // if user wants help, exit program
    if (displayHELP) {
        printUsage();
        return 0;
    }
    
    // create list with default parameters
    list = CreateList(ProcEntryPidCompar, ProcEntryToString, DestroyProcEntry);
    
    // set path to proc dir
    path = "/proc";
    
    // open proc dir ~ read PIDs at this point
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        exit(1);
    }

    struct dirent *ent;

    // iterate over 
    while ((ent = readdir(dir)) != NULL) {
        // make sure first char in string is number, else we have non-process entry
        bool isProc = true;
        for (int i = 0; ent->d_name[i] != '\0'; i++) {
            if (!isdigit(ent->d_name[i])) {
                isProc = false;
            }
        }

        if (isProc) {
            char *statPath = NULL;

            // asprintf to build path
            if (asprintf(&statPath, "/proc/%s/stat", ent->d_name) == -1) {
                perror("asprintf failed");
                continue;
            }

            // create entry from PID path
            entry = CreateProcEntryFromFile(statPath);
            // cleanup
            free(statPath);

            // error check
            if (entry == NULL) {
                perror("Error opening directory");
                exit(1);
            }
                
            // add validated process to list
            ListAppend(list, entry);
        }
    }
    // cleanup
    closedir(dir);

    // toString from project spec
    fprintf(stdout, "%7s %7s %5s %5s %5s %7s %-25s %-20s\n", "PID", "PPID", "STATE", "UTIME", "STIME", "THREADS", "CMD", "STAT_FILE");

    // sort list according to flags set by user
    if (displayByLEX) {
        list->Compar = ProcEntryCommCompar;
    } else {
        list->Compar = ProcEntryPidCompar;
    }

    // sort list before display 
    ListSort(list);

    // display list according to flags set by user
    if (displayZOMBIES) {
        ListPrint(list, ProcEntryZombieFilter);
    } else if (displayByMatchCOMM) {
        ListPrint(list, ProcEntryMatchCommFilter);
    } else {
        ListPrint(list, ProcEntryNoFilter);
    }

    DestroyList(list);
    return 0;
}