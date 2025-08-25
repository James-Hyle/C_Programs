# Setup a variable to reference the desired compiler
CC = gcc

# Setup a variable to hold desired compiler flags
CFLAGS = -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g

# Declaring the build, test and clean rules as phony means that no artifact
#   is created by these rules with a corresponding name. Therefore, the
#   rule should run when executed.
.PHONY: build test clean

# The build rule depends upon the main artifact existing. If it does not, make
#   will look for a rule to create it.
build: main

# the use of variables helps keep things very clean
# definitions for CC and CFLAGS are above
# $^ is an automatic variable for all the dependencies
# $@ is an automatic variable for the name of the target
main: main.o
	$(CC) $(CFLAGS) $^ -o $@

# make uses an implicit rule to generate the object file.

test: main
	./main

clean:
	rm -f *.o *.d *.s a.out main