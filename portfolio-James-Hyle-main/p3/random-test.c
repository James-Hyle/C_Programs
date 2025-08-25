#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "String.h"
#include "List.h"

const int NUM_TESTS = 7;
// const int DEBUG = 2;
const int DEBUG = 0;

/**
 * Print out stats for the random test.
 *
 * @param tests array of counters for each test type
 *
 * @return none
 */
void print_stats(int *tests) {
    printf(" ========================\n");
    printf(" Function  #invocations\n");
    printf(" ========================\n");
    printf(" ListAppend      %d \n", tests[0]);
    printf(" ListAdd(0)      %d \n", tests[1]);
    printf(" ListRemove      %d \n", tests[2]);
    printf(" ListRemove(0)   %d \n", tests[3]);
    printf(" ListRemove(end) %d \n", tests[4]);
    printf(" ListSort        %d \n", tests[5]);
    printf(" ListIndexOf     %d \n", tests[6]);
    printf(" ========================\n");
}

/* Create a simple String for testing */
static StringPtr createTestString(char *source, int i) {
    char *s;
    asprintf(&s, "%s #%d", source, i);
    StringPtr string = CreateString(s);
    free(s);
    return string;
}


/**
 * Run random tests on the given list.
 *
 * @param count number of tests to run
 * @param seed  random seed
 * @param n     size of the list
 * @param list  pointer to the list
 *
 * @return none
 */
void runRandomTests(int count, unsigned int seed, int n, ListPtr list) {
    int i;
    int test;
    StringPtr string;
    int *tests;

    tests = (int *)malloc(sizeof(int) * NUM_TESTS);
    for (i = 0; i < NUM_TESTS; i++)
        tests[i] = 0;

    srand(seed);
    for (i = 0; i < count; i++) {
        printf("\rRunning test #%d", i);
        test = (int)(NUM_TESTS * (double)rand() / RAND_MAX);
        tests[test]++;
        switch (test) {
        case 0:
            if (DEBUG > 1)
                fprintf(stderr, "ListAppend\n");
            n++;
            string = createTestString("some string ", n);
            ListAppend(list, string);
            break;
        case 1:
            if (DEBUG > 1)
                fprintf(stderr, "ListAdd(0)\n");
            n++;
            string = createTestString("some string ", n);
            ListAdd(list, 0, string);
            break;
        case 2:
            if (DEBUG > 1)
                fprintf(stderr, "ListRemove\n");
            string = ListRemove(list, i);
            DestroyString(string);
            break;
        case 3:
            if (DEBUG > 1)
                fprintf(stderr, "ListRemove(0)\n");
            string = ListRemove(list, 0);
            DestroyString(string);
            break;
        case 4:
            if (DEBUG > 1)
                fprintf(stderr, "ListRemove(end)\n");
            string = ListRemove(list, list->size - 1);
            DestroyString(string);
            break;
        case 5:
            if (DEBUG > 1)
                fprintf(stderr, "ListSort\n");
            ListSort(list, 0, ListSize(list) - 1);
            break;
        case 6:
            if (DEBUG > 1)
                fprintf(stderr, "ListIndexOf\n");
            string = createTestString("some string ", n);
            ListIndexOf(list, string);
            DestroyString(string);
            break;
        default:
            break;
        }
    }
    printf("\n");
    print_stats(tests);
    free(tests);
}

int main(int argc, char **argv) {
    int i;
    int n;
    int count;
    unsigned int seed = 0;

    StringPtr string;
    ListPtr list;

    if (argc < 2) {
        fprintf(stderr,
                "Usage: %s <list size> [<test size=list size>] [<seed>] \n",
                argv[0]);
        exit(1);
    }
    n = atoi(argv[1]);
    count = n;
    if (argc >= 3) {
        count = atoi(argv[2]);
    }
    if (argc == 4) {
        seed = (unsigned int)atoi(argv[3]);
    }

    list = CreateList();
    for (i = 0; i < n; i++) {
		string = createTestString("String ", i);
		ListAppend(list, string);
    }

    runRandomTests(count, seed, n, list);
    if (DEBUG > 0)
        ListPrint(list);

    DestroyList(list);
    return 0;
}
