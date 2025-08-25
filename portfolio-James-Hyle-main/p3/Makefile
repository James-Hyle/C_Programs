CC = gcc
CFLAGS = -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g -D_GNU_SOURCE
LFLAGS =

.PHONY = all clean test-all

PROGS=string-test simple-test list-test random-test
OBJECTS=List.o String.o

all: $(PROGS)

string-test: string-test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

simple-test: simple-test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

list-test: list-test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

random-test: random-test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

mem-test-list: random-test
	valgrind --leak-check=full --track-origins=yes ./random-test 10000 10000 123

clean:
	/bin/rm -f $(PROGS) *.o a.out *.d

