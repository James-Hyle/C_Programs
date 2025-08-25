#include <stdlib.h>
#include <stdio.h>

#include "List.h"


#define DEFAULT_SIZE 8

/* 
 * Constructs an empty list with the DEFAULT_SIZE.
 * Returns NULL upon failure
 */
ListPtr CreateList(void) {
    // allocate memory for list structure
    ListPtr L = (ListPtr)malloc(sizeof(List));

    // return NULL on failure
    if (!L) { return NULL; }
    
    // default size
    L->size = 0;
    L->maxSize = DEFAULT_SIZE;

    // allocate memory for array of strings in list
    L->array = (StringPtr *)malloc(sizeof(StringPtr) * L->maxSize);

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
        StringPtr temp = ListRemove(L, 0);
        DestroyString(temp);
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
StringPtr ListGet(ListPtr L, int index) {
    if (L == NULL || index < 0 || index > L->size) return NULL;

    // return stringptr at index
    return L->array[index];
}

/*
 * Returns the index of the first occurrence of the specified
 * element in this list, or -1 if this list does not contain the element
 * Returns -1 if L is NULL
 */
int ListIndexOf(ListPtr L, StringPtr element) {
    if (!L || !element) return -1;
    
    // iterate through array until element is found
    for (int i = 0; i < L->size; i++) {
        if (L->array[i] && 
            StringCompare(L->array[i], element) <= 0) {
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
void ListAdd(ListPtr L, int index, StringPtr element) {
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
void ListAppend(ListPtr L, StringPtr element) {
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
StringPtr ListRemove(ListPtr L, int index) {
    if (L == NULL || index < 0 || index >= L->size) { return NULL; }

    // keep reference to element to be removed
    StringPtr element = L->array[index];
    
    // replace position of removed element with element in back of array
    if (index < (L->size - 1)) {
        L->array[index] = L->array[L->size - 1];
    }
    
    // sanitize element at end of array
    L->array[L->size - 1] = NULL;
    L->size--;
    
    return element;
}

/* MergeSort elements in the list according to StringCompare */
void merge(ListPtr L, int l, int m, int r) {
    // Validate indices
    if (L == NULL || L->array == NULL || l < 0 || m < l || r < m || r >= L->size) return; 

    int lenL = m - l + 1;
    int lenR = r - m;
    int i;
    int j;
    int k;

    // allocate temp lists
    StringPtr *left = (StringPtr *)malloc(lenL * sizeof(StringPtr));
    StringPtr *right = (StringPtr *)malloc(lenR * sizeof(StringPtr));
    
    // copy strings in left side of original list to allocated list
    for (i = 0; i < lenL; i++) {
        left[i] = L->array[l + i];
    }

    // copy strings in right side of original list to allocated list
    for (j = 0; j < lenR; j++) {
        right[j] = L->array[m + 1 + j];
    }

    // merge lists according to StringCompare
    i = j = 0;
    k = l;

    while (i < lenL && j < lenR) {
        L->array[k++] = (StringCompare(left[i], right[j]) <= 0) ? left[i++] : right[j++];
    }

    // populate lists with remaining remaining elements in ascending order
    while (i < lenL) {
        L->array[k++] = left[i++];
    }
    while (j < lenR) {
        L->array[k++] = right[j++];
    }

    // deallocate temp arrays
    free(left);
    free(right);
}

/* sorts list using merge sort algorithm */
void ListSort(ListPtr L, int l, int r) {
    // Validate parameters
    if (L == NULL || L->array == NULL || l < 0 || r >= L->size || l >= r) {
        return;
    }

    const int m = l + (r - l) / 2;
    
    ListSort(L, l, m);
    ListSort(L, m + 1, r);
    merge(L, l, m, r);
}

/* Removes all of the elements from this list. */
void ListClear(ListPtr L) {
    if (L == NULL) return;
    
    // iterate through list and use DestroyString() to remove
    for (int i = 0; i < L->size; i++) {
        if (L->array[i] != NULL) {
            DestroyString(L->array[i]);
        }
    }
    
    L->size = 0;
}

/*
 * Prints a representation of this List.
 * The representation consists of the List's String's
 * in the order they are stored, separated by newlines.
 */
void ListPrint(ListPtr L) {
    if (L == NULL) { return; }

    // iterate through list and use StringToString to get a copy of string
    for (int i = 0; i < L->size; i++) {
        char *str = StringToString(L->array[i]);
        if (str != NULL) {
            printf("%s, ", str);
            // format: print ten elements before printing newline
            if (i % 10 == 0) { printf("\n"); }
            free(str);    
        }
    }
}

/* Provides room for more elements by doubling the array size. */
void ListGrow(ListPtr L) {
    if (L == NULL || L->array == NULL) return; 

    // get new size of array
    int new_maxSize = L->maxSize * 2;

    // reallocate memory according to StringPtr
    StringPtr *new_array = realloc(L->array, new_maxSize * sizeof(StringPtr));
    
    // return NULL on failure
    if (new_array == NULL) return;

    // update list 
    L->array = new_array;
    L->maxSize = new_maxSize;
}
