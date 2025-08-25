#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "String.h"

#define DEFAULT_SIZE 8

typedef struct list List;
typedef struct list *ListPtr;

struct list {
    int size;
    int maxSize;
    StringPtr *array;
};

/* 
 * Constructs an empty list with the DEFAULT_SIZE.
 * Returns NULL upon failure
 */
ListPtr CreateList(void);

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
StringPtr ListGet(ListPtr L, int index);

/* 
 * Returns the index of the first occurrence of the specified 
 * element in this list, or -1 if this list does not contain the element
 * Returns -1 if L is NULL
 */
int ListIndexOf(ListPtr L, StringPtr element);

/* 
 * Inserts the specified element at the specified position in this List
 * The element at index when the method is called is retained in the List
 * The order of the elements in the list is not specified after calling ListAdd
 * Does nothing if index is negative. Does nothing if index is greater than L->size
 */
void ListAdd(ListPtr L, int index, StringPtr element);

/*
 * Appends the specified element to the end of this list. 
 * Grows the array if more room is needed
 */
void ListAppend(ListPtr L, StringPtr element);

/*
 * Removes the element at the specified position in this List.
 * No gaps (elements that do not exist) are present in the List after calling
 */
StringPtr ListRemove(ListPtr L, int index);

/* Sorts the elements in the list according to StringCompare */
void ListSort(ListPtr L, int l, int r);

void merge(ListPtr L, int l, int m, int r);

/* Removes all of the elements from this list. */
void ListClear(ListPtr L);

/*
 * Prints a representation of this List.
 * The representation consists of the List's String's 
 * in the order they are stored, separated by newlines.
 */
void ListPrint(ListPtr L);

/* Provides room for more elements by doubling the array size. */
void ListGrow(ListPtr L);

#endif // LIST_H