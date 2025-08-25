#include <stdio.h>
#include <stdlib.h>

#include "file-info.h"
#include "List.h"


int main(int argc, char **argv) {
	int i;
	int n;
	FileInfo *dummyfile;
	ListPtr list;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <list size> \n", argv[0]);
		exit(1);
	}
	n = atoi(argv[1]);

	list = CreateList(FileInfoCompareSize, FileInfoToString, DestroyFileInfo);
	for (i = 0; i < n; i++) {
        char *s;
        asprintf(&s, "dummy file #%d", i);
		dummyfile = CreateFileInfo(s, 0L, 1024+i, 10);
		ListAppend(list, dummyfile);
        free(s);
	}

	ListPrint(list, FileInfoNoFilter);
    ListSort(list);
	ListPrint(list, FileInfoNoFilter);

	DestroyList(list);

	exit(0);
}