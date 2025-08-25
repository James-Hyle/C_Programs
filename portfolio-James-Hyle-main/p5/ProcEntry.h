/*
 * File: ProcEntry.h
 * Author(s): Andre Keys & Luke Hindman & Shane Panter
 * Description: Definition of ProcEntry struct and declaration
 *   of support functions used in the myps project.
 * 
 */
#ifndef __PROC_ENTRY_H
#define __PROC_ENTRY_H

#include <stdbool.h>

typedef struct {
     int process_id;
     int parent_process_id;
     char *comm;
     char state;
     unsigned long int utime;
     unsigned long int stime;
     long number_of_threads;
     char *path;
}ProcEntry;

/* CreateProcEntry: Allocate a ProcEntry struct in the heap using malloc.
 *   All fields will be initialized to zero or NULL based upon data type.
 * 
 * returns - Pointer to ProcEntry allocated on the heap, NULL on error
 */
ProcEntry *CreateProcEntry(void);

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
ProcEntry *CreateProcEntryFromFile(char statFile[]);


/* DestroyProcEntry: Release memory allocated by malloc in the
 *    CreateProcEntry or CreateProcEntryFromFile functions.  
 *    Does nothing if thisNode is NULL.
 * 
 * entry - Pointer to ProcEntry object to be freed.
 */
void DestroyProcEntry(void *entry);


/* ProcEntryToString: compose a string using the fields of the specified ProcEntry
 *    using the exact format specified in the project guide.
 * 
 * entry - Pointer to ProcEntry object to be stringified
 */
char *ProcEntryToString(const void *entry);


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
int ProcEntryPidCompar(const void *a, const void *b);


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
int ProcEntryCommCompar(const void *a, const void *b);


/* ProcEntryZombieFilter: Used to selectively identify ProcEntry.state == 'Z'
 *    returns true in the case that entry->state == 'Z'
 * 
 * entry - Pointer to ProcEntry
 */
bool ProcEntryZombieFilter(const void *entry);


/* ProcEntryNoFilter: Always returns true.
 * 
 * Suppress compilation warning of unused argument entry with:
 *    (void)(entry);
 * 
 * entry - Pointer to ProcEntry
 */
bool ProcEntryNoFilter(const void *entry);

int ProcEntryPidSort(const void *a, const void *b);

int ProcEntryLexSort(const void *a, const void *b);

#endif /* __PROC_ENTRY_H */