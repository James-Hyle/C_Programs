#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "ProcEntry.h"
#define UNUSED(x) (void)(x)

// exit gracefully
void exit_with_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

/* CreateProcEntry: Allocate a ProcEntry struct in the heap using malloc.
 *   All fields will be initialized to zero or NULL based upon data type.
 * 
 * returns - Pointer to ProcEntry allocated on the heap, NULL on error
 */
ProcEntry *CreateProcEntry(void) {
    ProcEntry *e = malloc(sizeof(ProcEntry));
    if (e == NULL) {
        exit_with_error("malloc fail");
    }

    e->process_id = 0;
    e->parent_process_id = 0;
    e->comm = NULL;
    e->state = '\0';
    e->utime = 0;
    e->stime = 0;
    e->number_of_threads = 0;
    e->path = NULL;
    return e;
}

/* CreateProcEntryFromFile: Allocate a ProcEntry struct in the heap 
 *    using malloc and initialize each field with data provided from
 *    the specified statFile. The command field (comm) and path field 
 *    will be allocated on the heap using malloc.
 * 
 * The statFile parameter must reference a stat file, formatted as 
 *    described in the /proc manpage entry. The statFile will be
 *    opened and the required fields extract to properly initialize
 *    the ProcEntry struct.
 *
 * If the statFile parameter is NULL or if the file does not exist, 
 *    return NULL. 
 * 
 * If the statFile exists, but an error occurs while attempting to 
 *    extract the field data because is not a properly formatted
 *    stat file, return NULL.
 *  
 * returns - Pointer to ProcEntry allocated on the heap, NULL on error
 */
ProcEntry *CreateProcEntryFromFile(char statFile[]) {
    const int NUM_TOKENS = 7;
    char *tokenArray[64];
    char *token;
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    int i;

    // allocate memory for ProcEntry
    ProcEntry *e = malloc(sizeof(ProcEntry));
    if (e == NULL) {
        exit_with_error("malloc fail");
    }

    // open stat file
    FILE *f = fopen(statFile, "r");
    if (f == NULL) {
        free(e);
        exit_with_error("fopen fail");
    }

    // set path
    e->path = strdup(statFile);

    // read stat line
    if ((linelen = getline(&line, &linecap, f)) == -1) {
        free(e);
        fclose(f);
        exit_with_error("getline fail");
    }

    // Tokenize line
    token = strtok(line, " ");

    i = 0;

    // populate token array with stat fields
    while (token != NULL) {
        tokenArray[i] = token;
        i++;
        token = strtok(NULL, " ");
    }

    // verify we got enough tokens
    if (i < NUM_TOKENS) {
        free(line);
        fclose(f);
        free(e);
        exit_with_error("not enough tokens in stat file");
    }

    // PROCESS PID ~ %d ~ POS: 0
    e->process_id = atoi(tokenArray[0]);

    // PROCESS COMM ~ %s ~ POS: 1 (enclosed in parentheses)
    // Remove parentheses from comm
    e->comm = strdup(tokenArray[1]);

    // PROCESS STATE ~ %c ~ POS: 2
    e->state = tokenArray[2][0];

    // PROCESS PPID ~ %d ~ POS: 3
    e->parent_process_id = atoi(tokenArray[3]);

    // PROCESS UTIME ~ %lu ~ POS: 13
    e->utime = strtoul(tokenArray[13], NULL, 10);

    // PROCESS STIME ~ %lu ~ POS: 14
    e->stime = strtoul(tokenArray[14], NULL, 10);

    // PROCESS NUMBER OF THREADS ~ %ld ~ POS: 19
    e->number_of_threads = strtol(tokenArray[19], NULL, 10);

    // Clean up
    free(line);
    fclose(f);

    return e;
}

/* DestroyProcEntry: Release memory allocated by malloc in the
 *    CreateProcEntry or CreateProcEntryFromFile functions.  
 *    Does nothing if thisNode is NULL.
 * 
 * entry - Pointer to ProcEntry object to be freed.
 */
void DestroyProcEntry(void *entry) {
    ProcEntry *e = (ProcEntry *)entry;
    // free fields before entry
    if (e->comm)
        free(e->comm);
    if (e->path)
        free(e->path);
    free(e);
}

/* ProcEntryToString: compose a string using the fields of the specified ProcEntry
 *    using the exact format specified in the project guide.
 * 
 * entry - Pointer to ProcEntry object to be stringified
 */
char *ProcEntryToString(const void *e) {
    ProcEntry *entry = (ProcEntry *)e;
    unsigned long int utime = entry->utime / sysconf(_SC_CLK_TCK);
    unsigned long int stime = entry->stime / sysconf(_SC_CLK_TCK);
    char *str;
    asprintf(&str, "%7d %7d %5c %5lu %5lu %7ld %-25s %-20s",
             entry->process_id,
             entry->parent_process_id,
             entry->state,
             utime,
             stime,
             entry->number_of_threads,
             entry->comm,
             entry->path);
    return str;
}

/* ProcEntryPidCompar: Perform comparison of two ProcEntry structs.
 *    a is compared to b by process_id. A negative value is
 *    returned if a's process_id is less than b's process_id.
 *    Zero is returned if both process_id's are the same. 
 *    A negative value is returned if a's process_id
 *    is less than b's process_id.
 * 
 *    Objects are type void * for compatibility with qsort.
 * 
 * a - void * to the first ProcEntry *
 * b - void * to the second ProcEntry *
 */
int ProcEntryPidCompar(const void *a, const void *b) {
    ProcEntry *f = *(ProcEntry **)a;
    ProcEntry *s = *(ProcEntry **)b;
    return f->process_id - s->process_id;
}

/* ProcEntryCommCompar: Perform comparison of two ProcEntry structs.
 *    a is compared to b by command. A negative value is
 *    returned if a's comm is less than b's comm via strmp.
 *    Zero is returned if both comm's are the same. 
 *    A negative value is returned if a's comm
 *    is less than b's comm via strcmp.
 * 
 *    Objects are type void * for compatibility with qsort.
 * 
 * a - void * to the first ProcEntry *
 * b - void * to the second ProcEntry *
 */
int ProcEntryCommCompar(const void *a, const void *b) {
    const ProcEntry *f = *(const ProcEntry **)a;
    const ProcEntry *s = *(const ProcEntry **)b;
    return strcmp(f->comm, s->comm);
}

/* ProcEntryZombieFilter: Used to selectively identify ProcEntry.state == 'Z'
 *    returns true in the case that entry->state == 'Z'
 * 
 * entry - Pointer to ProcEntry
 */
bool ProcEntryZombieFilter(const void *entry) {
    if (!entry)
        return false;

    const ProcEntry *e = (const ProcEntry *)entry;

    // Return true if process state is 'Z'
    return (e->state == 'Z');
}

/* ProcEntryNoFilter: Always returns true.
 * 
 * Suppress compilation warning of unused argument entry with:
 *    (void)(entry);
 * 
 * entry - Pointer to ProcEntry
 */
bool ProcEntryNoFilter(const void *entry) {
    UNUSED(entry);
    return true;
}