CC = gcc

CFLAGS = -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g

PROGS = shout whisper jn dedup cap

.PHONY: build test clean

build: $(PROGS)

shout: shout.o
	$(CC) $(CFLAGS) $^ -o $@

whisper: whisper.o
	$(CC) $(CFLAGS) $^ -o $@

jn: jn.o
	$(CC) $(CFLAGS) $^ -o $@

dedup: dedup.o
	$(CC) $(CFLAGS) $^ -o $@

cap: cap.o
	$(CC) $(CFLAGS) $^ -o $@

test: $(PROGS)
	./test.sh

clean:
	rm -f *.[odis] a.out $(PROGS) myout.txt
