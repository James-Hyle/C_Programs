#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include "file-info.h"

#define UNUSED(x) (void)(x)

FileInfo *CreateFileInfo(char *name, time_t mtime, off_t size, mode_t mode) {
    FileInfo *f = (FileInfo *) malloc(sizeof(FileInfo));

    f->name = strdup(name);
    f->mtime = mtime;
    f->size = size;
    f->mode = mode;

    return f;
}

void DestroyFileInfo(void *obj) {
    if (obj) {
        FileInfo *f = (FileInfo *)obj;
        free(f->name);
        free(f);
    }
}

bool FileInfoNoFilter(const void *obj) {
    UNUSED(obj);
    return true;
}

bool FileInfoDirFilter(const void *obj) {
    if (obj) {
        FileInfo *f = (FileInfo *)obj;
        return S_ISDIR(f->mode);
    } else {
        return false;
    }
}

int FileInfoCompareSize(const void *o1, const void *o2) {
    FileInfo *f = *(FileInfo **)o1;
    FileInfo *s = *(FileInfo **)o2;
    return s->size - f->size;
}

int FileInfoCompareTypeAndName(const void *o1, const void *o2) {
    FileInfo *f = *(FileInfo **)o1;
    FileInfo *s = *(FileInfo **)o2;
    if (S_ISDIR(f->mode) && S_ISDIR(s->mode)) {
        return strcmp(f->name, s->name);
    } else if (S_ISDIR(f->mode)) {
        return -1;
    } else if (S_ISDIR(s->mode)) {
        return 1;
    } else {
        return strcmp(f->name, s->name);
    }
}

int FileInfoCompareTime(const void *o1, const void *o2) {
    FileInfo *f = *(FileInfo **)o1;
    FileInfo *s = *(FileInfo **)o2;
    return f->mtime - s->mtime;
}

char *FileInfoToString(const void *obj) {

    if (obj) {
        FileInfo *t = (FileInfo *)obj;
        char *s;
        char time[26] = {0};
        ctime_r(&t->mtime, time);

        asprintf(&s, "%-10s\t%10lu\t%s", t->name, t->size, time);

        return s;

    } else {
        char *null = (char *) malloc(sizeof(int) * 5);
        strcpy(null, "NULL");
        return null;
    }
}