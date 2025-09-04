#define _GNU_SOURCE#include <stdio.h>

#include <stdlib.h>

#include <string.h>

char toUpper(char ch) {
  if (ch >= 'a' && ch <= 'z') {
    ch = ch & ~32;
  }
  return ch;
}

int main(void) {

  char * line = NULL;
  char * prevLine = NULL;
  size_t linecap = 0;
  ssize_t linelen;

  int i;

  while ((linelen = getline( & line, & linecap, stdin)) != -1) {
    i = 0; // set i to zero for each line
    if (prevLine != NULL) { // enter branch if prevLine exists
      while (i < linelen) {
        // if line has punctuation, first word is capitalized
        if (line[i] == '.' || line[i] == '?' || line[i] == '!') {
          putchar(line[i]); // print punctuation mark
          if (i + 1 < linelen && line[i + 1] == '\n') { // Handle newlines properly
            putchar(line[i + 1]);
            break;
          }
          if (i + 2 < linelen) { // Check if buffer will overflow
            putchar(line[i + 1]);
            putchar(toUpper(line[i + 2]));
            i += 3; // increment i to account for chars printed
          } else {
            i++;
          }
        } else { // normal buffer printing
          putchar(line[i]);
          i++;
        }
      }
    } else {
      while (i < linelen) {
        if (i == 0) {
          // capitalize first char of newline
          putchar(toUpper(line[0]));
          i++;
        }
        if (line[i] == '.' || line[i] == '?' || line[i] == '!') {
          putchar(line[i]);
          if (i + 1 < linelen && line[i + 1] == '\n') { // handle newlines 
            putchar(line[i + 1]);
            break;
          }
          if (i + 2 < linelen) {
            putchar(line[i + 1]);
            putchar(toUpper(line[i + 2]));
            i += 3;
          } else {
            i++;
          }
        } else {
          putchar(line[i]);
          i++;
        }
      }
      prevLine = line;
    }
  }

  free(line);
  return 0;
}
