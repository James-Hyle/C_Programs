CC = gcc
CFLAGS = -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g -D_GNU_SOURCE
LFLAGS =

.PHONY = all clean

all: myls

myls: List.o myls.o file-info.o
	$(CC) $(CFLAGS) $^ -o $@

List.o: List.c
	$(CC) $(CFLAGS) $^ -c -o $@

simple-test: simple-test.o List.o file-info.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	/bin/rm -f $(PROGS) *.o a.out *.d ./myls