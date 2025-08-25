#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_SIZE 8

typedef struct list List;
typedef struct list *ListPtr;

struct list {
    int size;
    int maxSize;
    void **array;

    int (*Compar)(const void *, const void *);
    char *(*ToString)(const void *);
    void (*DestroyObject)(void *);
};

/* 
 * Constructs an empty list with the DEFAULT_SIZE.
 * Returns NULL upon failure
 */
ListPtr CreateList(int (*Compar)(const void *, const void *), char *(*ToString)(const void *), void (*DestroyObject)(void *));

/* frees all memory associated with the list */
void DestroyList(ListPtr L);

/* Returns the number of elements in this list, or -1 if L is NULL */
int ListSize(ListPtr L);

/* Returns true if this list contains no elements, or if L is NULL */
bool ListIsEmpty(ListPtr L);

/* 
 * Returns the element at the specified position in this list
 * Returns NULL if index is beyond the bounds of the List or L is NULL
 */
void *ListGet(ListPtr L, int index);

/* 
 * Returns the index of the first occurrence of the specified 
 * element in this list, or -1 if this list does not contain the element
 * Returns -1 if L is NULL
 */
int ListIndexOf(ListPtr L, void *element);

/* 
 * Inserts the specified element at the specified position in this list.
 * shifts the elements in List to make room if necessary
 * Does nothing if index is negative. Does nothing if index is greater than L->size
 */
void ListAdd(ListPtr L, int index, void *element);

/*
 * Appends the specified element to the end of this list. 
 * Grows the array if more room is needed
 */
void ListAppend(ListPtr L, void *element);

/*
 * Removes the element at the specified position in this list.
 * shifts the elements to fill the gap if necessary
 */
void *ListRemove(ListPtr L, int index);

/* Sorts the elements in the list according to L->Compar */
void ListSort(ListPtr L);

/* mergeSort algorithm */
void merge(ListPtr L, int l, int m, int r);

/* Removes all of the elements from this list. */
void ListClear(ListPtr L);

/*
 * Prints a representation of this List.
 * The representation consists of the List's Objects 
 * in the order they are stored, separated by newlines.
 * 
 * filter is a function that returns true if an element is to be
 * printed, and false if not
 */
void ListPrint(ListPtr L, bool (*filter)(const void *));

/* Provides room for more elements by doubling the array size. */
void ListGrow(ListPtr L);

char *mystrcpy(char *d, const char *s);

#endif // LIST_H