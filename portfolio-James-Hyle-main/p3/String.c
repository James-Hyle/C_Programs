#include <stdlib.h>
#include <stdio.h>

#include "String.h"

#define DEFAULT_SIZE 8

/*
 * string copy method 
 */
char *mystrcpy(char *d, const char *s) {
    char *dest = d;
    while ((*d++ = *s++) != '\0');
    return dest;
}

/* 
 * returns the length of a string 
 */
int mystrlen(const char *s) {
    int count = 0;
    while (*s != '\0') {
        s++;
        count++;
    }

    return count;
}

/*
 * Allocates a new String struct that contains a *copy* of s
 * Returns the newly allocated struct, or NULL upon failure
 */
StringPtr CreateString(const char *s) {
    // Reject NULL input immediately
    if (!s) return NULL;

    // Allocate and zero-initialize String struct
    String *newString = calloc(1, sizeof(String));
    if (!newString) return NULL;

    // Calculate length using your mystrlen function
    size_t len = mystrlen(s);
    
    // Allocate and copy string
    if (!(newString->s = malloc(len + 1))) {
        free(newString);
        return NULL;
    }
    
    // Use your mystrcpy function for copying
    mystrcpy(newString->s, s);
    
    newString->length = len;
    return newString;
}

/*
 * returns the character at position i in StringPtr S
 * if i exceeds the length of S, return '\0'
 */
char CharAt(const StringPtr S, int i) {
    if (i > S->length - 1 || i < 0) {
        return '\0';
    } 
    
    return S->s[i];
    
}

/*
 * return <0 if S1 < S2, 0 if S1 == S2, >0 if S1 > S2
 */
int StringCompare(const StringPtr S1, const StringPtr S2) {
    if (!S1 || !S2) {
        if (!S1 && !S2) return 0;  // Both NULL are equal
        return S1 ? 1 : -1;         // NULL is considered less than non-NULL
    }

    if (S1->length != S2->length) {
        return S1->length > S2->length ? 1 : -1;
    }

    for (int i = 0; i < S1->length; i++) {
        if (S1->s[i] != S2->s[i]) {
            return (S1->s[i] > S2->s[i]) ? 1 : -1;
        }
    }

    return 0;
}

/*
 * return a C-string *copy* of the String S
 * does not use sprintf for security reasons
 * uses asprintf instead
 */
char *StringToString(const StringPtr S) {
    char *toString;
    if (S) {
        asprintf(&toString, "%s", S->s);
        return toString;
    } 
    return NULL;

}

/*
 * frees all of the memory associated with S
 */
void DestroyString(StringPtr S) {
    if (S) {
        free(S->s);  
        free(S); 
    }
}
