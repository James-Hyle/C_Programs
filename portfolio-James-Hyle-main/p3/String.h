#ifndef STRING_H
#define STRING_H

typedef struct string String;
typedef struct string *StringPtr;

struct string {
    char *s;
    int length;
};

/*
 * Allocates a new String struct that contains a *copy* of s
 * Returns the newly allocated struct, or NULL upon failure
 */
StringPtr CreateString(const char *s);

/* 
 * returns the character at position i in StringPtr S 
 * if i exceeds the length of S, return '\0'
 */
char CharAt(const StringPtr S, int i);

/*
 * return <0 if S1 < S2, 0 if S1 == S2, >0 if S1 > S2
 */
int StringCompare(const StringPtr S1, const StringPtr S2);

/*
 * return a C-string *copy* of the String S
 * does not use sprintf for security reasons
 * uses asprintf instead
 */
char *StringToString(const StringPtr S);

/*
 * frees all of the memory associated with S
 */
void DestroyString(StringPtr S);

#endif // STRING_H