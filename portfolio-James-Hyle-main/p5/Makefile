CC = gcc
CFLAGS = -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g
LFLAGS =

LIST_DIR = ./list

.PHONY = all clean

PROGS=myps orphan zombie daemon proc-entry-test
OBJECTS=List.o myps.o ProcEntry.o 

all: $(PROGS)

myps: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

orphan: orphan.o
	$(CC) $(CFLAGS) $^ -o $@

daemon: daemon.o
	$(CC) $(CFLAGS) $^ -o $@

zombie: zombie.o
	$(CC) $(CFLAGS) $^ -o $@

proc-entry-test: proc-entry-test.o ProcEntry.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	/bin/rm -f $(PROGS) *.o a.out *.d

