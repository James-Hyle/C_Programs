#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "String.h"

/* 
 * macro to mimic the functionality of assert() from <assert.h>. The difference is that this version doesn't exit the program entirely.
 * It will just break out of the current function (or test case in this context).
 */
#define myassert(expr) if(!(expr)){ fprintf(stderr, "\t[assertion failed] %s: %s\n", __PRETTY_FUNCTION__, __STRING(expr)); return false; }

int testCount = 0;
int passCount = 0;

StringPtr string; //test subject

void printTestInfo(char *testName, char *info) {
	fprintf(stdout, "%s - %s\n", testName, info);
}

void printTestResult(char *testName, bool passed) {
	if(passed == true)
		fprintf(stdout, "%s - %s\n\n", "[PASSED]", testName);
	else
		fprintf(stdout, "%s - %s\n\n", "[FAILED]", testName);
}

/* Test Case Definitions */

bool testStringLength(void) {

	string = CreateString("hello");
	myassert(string->length == 5)
	DestroyString(string);
    
	string = CreateString("test");
	myassert(string->length == 4)
	DestroyString(string);

	return true;
}

bool testStringCharAt(void) {

	string = CreateString("hello1");
	myassert(CharAt(string, 0) == 'h')

	myassert(CharAt(string, 1) == 'e')

	myassert(CharAt(string, 2) == 'l')

	myassert(CharAt(string, 3) == 'l')

	myassert(CharAt(string, 4) == 'o')

	myassert(CharAt(string, 5) == '1')

	myassert(CharAt(string, 6) == '\0') //out of bounds
	myassert(CharAt(string, -1) == '\0') //out of bounds

	DestroyString(string);

	return true;
}

bool testStringCompare(void) {

	string = CreateString("abcde");
    StringPtr string2 = CreateString("abcdef");

	myassert(StringCompare(string, string2) < 0)

	myassert(StringCompare(string2, string) > 0)

	myassert(StringCompare(string, string) == 0)

    DestroyString(string2);

	DestroyString(string);

	return true;
}

bool testStringToString(void) {

	string = CreateString("abcde");
    char *s = StringToString(string);

	myassert(s != string->s) // make sure they don't point to the same place

	myassert(strcmp(s, string->s) == 0) // they are the same contents

    free(s);

	DestroyString(string);

	return true;
}

void beforeTest(char* testName) {
	printTestInfo(testName, "Running...");
	testCount++;
}

void afterTest(char* testName, bool result) {
	printTestResult(testName, result);
	passCount += result;
}

void runUnitTests(void) {
	bool result;
	char *testName;

	testName = "testStringLength";
	beforeTest(testName);
	result = testStringLength();
	afterTest(testName, result);

	testName = "testStringCharAt";
	beforeTest(testName);
	result = testStringCharAt();
	afterTest(testName, result);

	testName = "testStringCompare";
	beforeTest(testName);
	result = testStringCompare();
	afterTest(testName, result);

	testName = "testStringToString";
	beforeTest(testName);
	result = testStringToString();
	afterTest(testName, result);

	fprintf(stdout, "Test Cases: %d\n",  testCount);
	fprintf(stdout, "Passed: %d\n", passCount);
	fprintf(stdout, "Failed: %d\n", testCount - passCount);
}

int main(void) {
	runUnitTests();
	exit(0);
}
