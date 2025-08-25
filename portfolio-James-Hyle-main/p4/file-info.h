#ifndef FILE_INFO_H
#define FILE_INFO_H

#include <stdbool.h>

typedef struct {
    char *name;
    time_t mtime;
    off_t size;
    mode_t mode;
} FileInfo;

/**
 *  Output: Pointer to allocated memory for FileInfo
 *  Creates a file information object with a given:
 *      - name:  File name
 *      - mtime: Time file last modified
 *      - size:  size of file 
 *      - mode:  file permission (rwx)
 *  User's responsability to free memory associated with created objects!!
 */
FileInfo *CreateFileInfo(char *name, time_t mtime, off_t size, mode_t mode);

/**
 *  Output: Free memory associated with FileInfo Object.
 *  Free f->name, and then f object.
 */
void DestroyFileInfo(void *);

/**
 *  Output: Unused ~ Always return true, so print w/out filtering.
 */
bool FileInfoNoFilter(const void *obj);

/**
 *  Output: Return true iff FileInfo object is a directory.
 */
bool FileInfoDirFilter(const void *obj);

/**
 *  Output: Integer indicating which of two FileInfo objects is larger.
 *      - Positive: o1 has greater memory size
 *      - Zero: Objects are of equal memory size
 *      - Negative: o2 has greater memory size
 */
int FileInfoCompareSize(const void *o1, const void *o2);


/**
 *  Output: Integer indicating which of two FileInfo objects.
 *      - Positive: o1 has greater memory size
 *      - Zero: Objects are of equal memory size
 *      - Negative: o2 has greater memory size
 */
int FileInfoCompareTypeAndName(const void *o1, const void *o2);

/**
 *  Output: Integer indicating which FileInfo object modification time is earlier.
 *      - Positive: o1 has been modified earlier 
 *      - Zero: Objects were modified at the same time
 *      - Negative: o2 has been modified earlier
 */
int FileInfoCompareTime(const void *o1, const void *o2);

/**
 *  Output: Formatted C-string representation of FileInfoObject.
 *  Format: < t->name   t->size   time >
 *      - t->name: Name of FileInfo Object. 
 *      - t->size: Unsigned long holding size of object.
 *      - time: Time file was last modified. 
 *  User's responsability to free memory associated with created objects!!
 */
char *FileInfoToString(const void *);

#endif