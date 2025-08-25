#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "String.h"
#include "List.h"

/* 
 * macro to mimic the functionality of assert() from <assert.h>. The difference is that this version doesn't exit the program entirely.
 * It will just break out of the current function (or test case in this context).
 */
#define myassert(expr) if(!(expr)){ fprintf(stderr, "\t[assertion failed] %s: %s\n", __PRETTY_FUNCTION__, __STRING(expr)); return false; }

ListPtr testlist;

int testCount = 0;
int passCount = 0;

void printTestInfo(char* testName, char *info) {
	fprintf(stdout, "%s - %s\n", testName, info);
}

void printTestResult(char* testName, bool passed) {
	if(passed == true)
		fprintf(stdout, "%s - %s\n\n", "[PASSED]", testName);
	else
		fprintf(stdout, "%s - %s\n\n", "[FAILED]", testName);
}

/* Create a simple String for testing */
static StringPtr createTestString(char *source, int i) {
    char *s;
    asprintf(&s, "%s #%d", source, i);
    StringPtr string = CreateString(s);
    free(s);
    return string;
}


/* Test Case Definitions */

// add single element to empty list
bool appendInEmptyList(void) {

	StringPtr obj = CreateString("test string");

    ListAppend(testlist, obj);

	myassert(testlist->size == 1)
	myassert(testlist->maxSize == DEFAULT_SIZE)
    StringPtr obj2 = ListGet(testlist, 0);
	myassert(obj == obj2)           //testing that the addresses are the same
	myassert(obj->s == obj2->s)     //testing that the addresses are the same
	myassert(strcmp(obj->s, obj2->s) == 0)      // contents are the same
	myassert(obj->length == obj2->length)       // contents are the same

	return true;
}

// size of list
bool listSize(void) {
	int i;

	// check testlist size is 0 on init
	myassert(ListSize(testlist) == 0)

    for (i = 0; i < 10; i++) {
		StringPtr obj = createTestString("test", i);
        ListAppend(testlist, obj);
    }

	// check size after adding elements to list
	myassert(ListSize(testlist) == 10)
	
	return true;
}

// empty or null list
bool listIsEmpty(void) {

    myassert(testlist != NULL);
    myassert(ListIsEmpty(testlist) == true);
    myassert(ListIsEmpty(NULL) == true);

    for (int i = 0; i < 8; i++) {
        StringPtr obj = createTestString("test", i);
        myassert(obj != NULL);
        ListAppend(testlist, obj);
    }

    myassert(ListIsEmpty(testlist) == false);

    while (testlist->size > 0) {
        StringPtr removed = ListRemove(testlist, 0);
        DestroyString(removed);
    }
    myassert(ListIsEmpty(testlist) == true);

    return true;
}

// list get
bool listGet(void) {
    StringPtr obj = CreateString("StringToGet");    
    ListAdd(testlist, 0, obj);

    myassert(ListGet(testlist, 0) == obj);
    
    StringPtr element = ListGet(testlist, 0);
    myassert(element != NULL);
    myassert(strcmp(obj->s, element->s) == 0);
    myassert(obj->length == element->length);
    
    myassert(ListGet(testlist, -1) == NULL);
    myassert(ListGet(testlist, 1000) == NULL);
    myassert(ListGet(NULL, 0) == NULL);
    
    return true;
}

// list index
bool listIndexOf(void) {
    
    StringPtr obj = CreateString("indexString");
	StringPtr obj2 = CreateString("indexString2");

    ListAppend(testlist, obj);
	ListAppend(testlist, obj2);

    myassert(ListIndexOf(testlist, obj) == 0);
	myassert(ListIndexOf(testlist, obj2) == 0);

    return true;
}

// list add
bool listAdd(void) {
    StringPtr obj1 = CreateString("first");
    ListAdd(testlist, 0, obj1);

    myassert(ListSize(testlist) == 1);
    myassert(ListGet(testlist, 0) == obj1);

    StringPtr obj2 = CreateString("second");
    ListAdd(testlist, 0, obj2);

    myassert(ListSize(testlist) == 2);
    myassert(ListGet(testlist, 0) == obj2);
    myassert(ListGet(testlist, 1) == obj1);

    StringPtr obj3 = CreateString("middle");
    ListAdd(testlist, 1, obj3);

    myassert(ListSize(testlist) == 3);
    myassert(ListGet(testlist, 0) == obj2); 
    myassert(ListGet(testlist, 1) == obj3);
    myassert(ListGet(testlist, 2) == obj1);

    StringPtr obj4 = CreateString("last");    
    ListAdd(testlist, 3, obj4);

    myassert(ListSize(testlist) == 4);
    myassert(ListGet(testlist, 3) == obj4);

    StringPtr obj5 = CreateString("badadd");
    ListAdd(testlist, -1, obj5);
    myassert(ListSize(testlist) == 4);
    DestroyString(obj5);

    obj5 = CreateString("badadd");
    ListAdd(testlist, 100, obj5);
	myassert(ListSize(testlist) == 4);
	DestroyString(obj5);

    ListAdd(NULL, 0, obj4);
    ListAdd(testlist, 0, NULL); 
    myassert(ListSize(testlist) == 4);

    return true;
}

// double size of list
bool growList(void) {
	int initialCapacity = testlist->maxSize;
	myassert(initialCapacity == 8);

	for (int i = 0; i < initialCapacity; i++) {
		StringPtr obj = createTestString("test", i);
		ListAppend(testlist, obj);
		myassert(testlist->size == i + 1);
		myassert(testlist->maxSize == initialCapacity); 
	}

	StringPtr* oldArray = testlist->array;
	StringPtr growthObj = CreateString("growthTest");
	ListAppend(testlist, growthObj);

	myassert(testlist->size == initialCapacity + 1);
	myassert(testlist->maxSize > initialCapacity);
	myassert(testlist->array != oldArray);

	for (int i = 0; i < initialCapacity; i++) {
		StringPtr obj = ListGet(testlist, i);
		myassert(obj != NULL);
		myassert(strstr(obj->s, "test") != NULL);
	}

	myassert(ListGet(testlist, initialCapacity) == growthObj);

	int preGrowthSize = testlist->size;
	int preGrowthCapacity = testlist->maxSize;

	for (int i = 0; i < preGrowthCapacity; i++) {
		StringPtr obj = createTestString("additional", i);
		myassert(obj != NULL);
		ListAppend(testlist, obj);
	}

	myassert(testlist->size == preGrowthSize + preGrowthCapacity);
	myassert(testlist->maxSize > preGrowthCapacity);

	return true;
}

// list create
bool createList(void) {
	myassert(testlist != NULL);
    myassert(testlist->size == 0);
    myassert(testlist->maxSize == 8); 
    myassert(testlist->array != NULL); 

    for (int i = 0; i < testlist->maxSize; i++) {
        myassert(testlist->array[i] == NULL); 
    }

    StringPtr testStr = CreateString("test");

    myassert(testStr != NULL);
    
    ListAppend(testlist, testStr);

    myassert(testlist->size == 1);
    myassert(ListIsEmpty(testlist) == false);
    myassert(ListGet(testlist, 0) == testStr);
    myassert(ListIndexOf(testlist, testStr) == 0);

    return true;
}

// list remove
bool removeList(void) {
    ListPtr testList = CreateList();

    myassert(testList != NULL);

    StringPtr items[3];

    for (int i = 0; i < 3; i++) {
        items[i] = CreateString("test");
        myassert(items[i] != NULL);
        ListAppend(testList, items[i]);
    }

    myassert(ListSize(testList) == 3);

    StringPtr removed = ListRemove(testList, 1);
    myassert(removed == items[1]);
    myassert(ListSize(testList) == 2);
    myassert(ListGet(testList, 1) == items[2]);
    DestroyString(removed); 

    removed = ListRemove(testList, 0);
    myassert(removed == items[0]);
    myassert(ListSize(testList) == 1);
    DestroyString(removed);

    removed = ListRemove(testList, 0); 
    myassert(removed == items[2]);
    myassert(ListSize(testList) == 0);
    DestroyString(removed);

    removed = ListRemove(testList, 0);
    myassert(removed == NULL);
    myassert(ListSize(testList) == 0);

    removed = ListRemove(testList, -1);
    myassert(removed == NULL);
    
    removed = ListRemove(testList, 100);
    myassert(removed == NULL);

    removed = ListRemove(NULL, 0);
    myassert(removed == NULL);

    DestroyList(testList);
    return true;
}

bool clearList(void) {
    myassert(testlist != NULL);
    myassert(ListSize(testlist) == 0);

    ListClear(testlist);
    myassert(ListSize(testlist) == 0);


    for (int i = 0; i < testlist->maxSize; i++) {
        myassert(testlist->array[i] == NULL);
    }

    StringPtr newItem = CreateString("new_item");
    myassert(newItem != NULL);
    ListAppend(testlist, newItem);
    myassert(ListSize(testlist) == 1);
    myassert(ListGet(testlist, 0) == newItem);
    myassert(strcmp(ListGet(testlist, 0)->s, "new_item") == 0);

    return true;
}

bool sortList(void) {
    ListClear(testlist);
    ListSort(testlist, 0, -1);
    myassert(ListSize(testlist) == 0);

    StringPtr single = CreateString("single");
    myassert(single != NULL);
    ListAppend(testlist, single);
    ListSort(testlist, 0, 0);
    myassert(ListSize(testlist) == 1);
    myassert(StringCompare(ListGet(testlist, 0), single) == 0);

    ListClear(testlist);
    StringPtr apple = CreateString("apple");
    StringPtr banana = CreateString("banana");
    StringPtr cherry = CreateString("cherry");
    
    ListAppend(testlist, cherry);
    ListAppend(testlist, banana);
    ListAppend(testlist, apple);
    
    ListSort(testlist, 0, 2);
    myassert(StringCompare(ListGet(testlist, 0), apple) == 0);
    myassert(StringCompare(ListGet(testlist, 1), banana) == 0);
    myassert(StringCompare(ListGet(testlist, 2), cherry) == 0);

    return true;
}

/*
 * etc...
 */

void beforeTest(char* testName) {
	printTestInfo(testName, "Running...");
	testlist = CreateList();
	testCount++;
}

void afterTest(char* testName, bool result) {
	printTestResult(testName, result);
	DestroyList(testlist);
	passCount += result;
}

void runUnitTests(void) {
	bool result;
	char *testName;

	testName = "appendInEmptyList";
	beforeTest(testName);
	result = appendInEmptyList();
	afterTest(testName, result);

	testName = "listSize";
	beforeTest(testName);
	result = listSize();
	afterTest(testName, result);

	testName = "listIsEmpty";
	beforeTest(testName);
	result = listIsEmpty();
	afterTest(testName, result);

	testName = "listGet";
	beforeTest(testName);
	result = listGet();
	afterTest(testName, result);

	testName = "listIndexOf";
	beforeTest(testName);
	result = listIndexOf();
	afterTest(testName, result);

	testName = "listAdd";
	beforeTest(testName);
	result = listAdd();
	afterTest(testName, result);	

	testName = "growList";
	beforeTest(testName);
	result = growList();
	afterTest(testName, result);

	testName = "createList";
	beforeTest(testName);
	result = createList();
	afterTest(testName, result);

	testName = "removeList";
	beforeTest(testName);
	result = removeList();
	afterTest(testName, result);

	testName = "clearList";
	beforeTest(testName);
	result = clearList();
	afterTest(testName, result);

	testName = "sortList";
	beforeTest(testName);
	result = sortList();
	afterTest(testName, result);

	//etc...

	fprintf(stdout, "Test Cases: %d\n",  testCount);
	fprintf(stdout, "Passed: %d\n", passCount);
	fprintf(stdout, "Failed: %d\n", testCount - passCount);
}

int main(void) {
	runUnitTests();
	exit(0);
}
