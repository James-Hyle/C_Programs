#include <stdlib.h>
#include <stdio.h>

#include "List.h"

#define DEFAULT_SIZE 8

/* 
 * Constructs an empty list with the DEFAULT_SIZE.
 * Returns NULL upon failure
 */
ListPtr CreateList(int (*Compar)(const void *, const void *), char *(*ToString)(const void *), void (*DestroyObject)(void *)) {
    // allocate memory for list structure
    ListPtr L = (ListPtr)malloc(sizeof(List));

    // return NULL on failure
    if (!L) return NULL;

    // default size
    L->size = 0;
    L->maxSize = DEFAULT_SIZE;
    
    L->Compar = Compar;
    L->ToString = ToString;
    L->DestroyObject = DestroyObject;

    // allocate memory for array of objects in list
    L->array = (void *)malloc(sizeof(void*) * L->maxSize);
    // return NULL on failure
    if (!L->array) { return NULL; }

    // init all array elements to NULL
    for (int i = 0; i < L->maxSize; i++) 
        L->array[i] = NULL;

    return L;
}

/* frees all memory associated with the list */
void DestroyList(ListPtr L) {
    if (!L) return;
    
    // call DestroyString() on each element in list to remove
    while (L->size > 0) {
        void * temp = ListRemove(L, 0);
        L->DestroyObject(temp);
    }
    
    // free memory in list
    free(L->array);
    free(L);
}

/* returns the number of elements in this list, or -1 if L is NULL */
int ListSize(ListPtr L) {
    if (L == NULL) return -1;
    
    // get size of list
    return L->size;
}

/* Returns true if this list contains no elements, or if L is NULL */
bool ListIsEmpty(ListPtr L) {
    if (L == NULL) return true;
    
    // check if size equals zero
    return (L->size == 0);
}

/*
 * Returns the element at the specified position in this list
 * Returns NULL if index is beyond the bounds of the List or L is NULL
 */
void *ListGet(ListPtr L, int index) {
    if (L == NULL || index < 0 || index > L->size) return NULL;

    // return void * at index
    return L->array[index];
}

/*
 * Returns the index of the first occurrence of the specified
 * element in this list, or -1 if this list does not contain the element
 * Returns -1 if L is NULL
 */
int ListIndexOf(ListPtr L, void *element) {
    if (!L || !element) return -1;

    // iterate through array until element is found
    for (int i = 0; i < L->size; i++) {
        if (L->array[i] && L->Compar(L->array[i], element) == 0) {
            return i;
        }
    }
    return -1;
}

/*
 * Inserts the specified element at the specified position in this List
 * The element at index when the method is called is retained in the List
 * ListAdd
 * Does nothing if index is negative. Does nothing if index is greater than L->size
 */
void ListAdd(ListPtr L, int index, void *element) {
    if (L == NULL || element == NULL || index < 0 || index > L->size) return;

    // guard
    if (L->size >= L->maxSize) ListGrow(L);

    // put current element at index to back of array, appends if index is at size
    L->array[L->size] = L->array[index];
    // replace current with new element
    L->array[index] = element;
    L->size++;
}


/*
 * Appends the specified element to the end of this list.
 * Grows the array if more room is needed
 */
void ListAppend(ListPtr L, void *element) {
    if (L == NULL || element == NULL) return;
    
    // guard
    if (L->size >= L->maxSize) ListGrow(L);
    
    // Use list add to put element in back
    ListAdd(L, L->size, element);
}

/*
 * Removes the element at the specified position in this List.
 * No gaps (elements that do not exist) are present in the List after calling
 */
void *ListRemove(ListPtr L, int index) {
    if (L == NULL || index < 0 || index >= L->size) { return NULL; }

    // keep reference to element to be removed
    void *element = L->array[index];
    
    // replace position of removed element with element in back of array
    if (index < (L->size - 1)) {
        L->array[index] = L->array[L->size - 1];
    }
    
    // sanitize element at end of array
    L->array[L->size - 1] = NULL;
    L->size--;
    
    return element;
}

/* sorts list using merge sort algorithm */
void ListSort(ListPtr L) {
    
    // check if L is NULL
    if (L == NULL) return;

    qsort(L->array, L->size, sizeof(ListPtr), L->Compar); 
}

/* Removes all of the elements from this list. */
void ListClear(ListPtr L) {
    if (L == NULL) return;
    
    // iterate through list and use DestroyString() to remove
    for (int i = 0; i < L->size; i++) {
        if (L->array[i] != NULL) {
            free(L->array[i]);
        }
    }
    free(L);
    
    L->size = 0;
}

/*
 * Prints a representation of this List.
 * The representation consists of the List's String's
 * in the order they are stored, separated by newlines.
 */
void ListPrint(ListPtr L, bool (*filter)(const void *)) {
    if (L == NULL) return;
    
    int i = 0;
    while (i < L->size) {
        // pass single element to filter func 
        if (filter(L->array[i])) {
            char *s = L->ToString(L->array[i]); 
            printf("%s\n", s);
            free(s);  
        }
        i++;
    }
}

/* Provides room for more elements by doubling the array size. */
void ListGrow(ListPtr L) {
    if (L == NULL || L->array == NULL) return; 

    // get new size of array
    int new_maxSize = L->maxSize * 2;

    // reallocate memory according to void *
    void * *new_array = realloc(L->array, new_maxSize * sizeof(void *));
    
    // return NULL on failure
    if (new_array == NULL) return;

    // update list 
    L->array = new_array;
    L->maxSize = new_maxSize;
}