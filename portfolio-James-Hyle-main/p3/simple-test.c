#include <stdio.h>
#include <stdlib.h>

#include "String.h"
#include "List.h"


int main(int argc, char **argv) {
	int i;
	int n;
	StringPtr string;
	ListPtr list;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <list size> \n", argv[0]);
		exit(1);
	}
	n = atoi(argv[1]);

	list = CreateList();
	for (i = 0; i < n; i++) {
        char *s;
        asprintf(&s, "String #%d", i);
		string = CreateString(s);

		ListAdd(list, 0, string);
        free(s);
	}

	ListPrint(list);
    ListSort(list, 0, ListSize(list) - 1);
	ListPrint(list);

	DestroyList(list);

	exit(0);
}
