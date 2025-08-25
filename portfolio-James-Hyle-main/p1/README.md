# Project #1: Fun with Bits

* Author: James Hyle
* Class: CS253 Section #001
* Semester: Spring '25

## Overview

This program will swap endianness in an memory address passed in through the command line. It should take the MSB(Most Significant Byte) and swap its place with the LSB(Least Significant Byte). The second MSB will be swapped with the second LSB. x1-x2-x3-x4 --> x4-x3-x2-x1


## Reflection

This project was a really cool journey into the C language. I am not used to the syntax
of C which was my biggest speedbump. I spent a lot of time writing a function and
refactoring after I realized what could be made easier to read and more concise. I am
liking C a lot so far, it is different than Java, and I am really curious to see how c
can scale into a larger program. I am excited to learn more about composing files
together because I have a very basic understanding of dependency management. I have a
plethora of questions after this project, and I am excited to learn more.

I spent a bit of time working on a recursive function to print the bits in a value.I
thought it was a cool challenge for myself, and I am satisfied with the method, but I am
not versed enough in C to prepend the leading zeros before the result. I am wondering if
the bit shifting methods are able to accomplish this? I am curious about what else can
be accomplished with shifting, they are the most powerful low level data manipulation
techniques I have seen. I struggled quite a bit at first with the bitshifting, and I
believe my implementation will only work with 32 bit numbers due to how I constructed
the logic in my for loop using the get bits method. I am curious to see if there is a
more general algorithm to swap the endianness of values, no matter how many bits are
contained.

## Compiling and Using

Use the command make to compile and produce an executable file "endian". You can pass an
integer in through the command line upon execution of endian, or use the test.sh script
to pass in 5 cases demonstrating the program's functionality.

## Results

[jameshyle@onyx p1]$ make
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g   -c -o endian.o endian.c
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g endian.o -o endian
[jameshyle@onyx p1]$ ./test.sh
Executing test using input file testdata/test.in.

All tests passed!

[jameshyle@onyx p1]$

myresult.out:
Decimal         Binary                              Hexadecimal
----------------------------------------------------------------
x  0            00000000000000000000000000000000   0x00000000
x' 0            00000000000000000000000000000000   0x00000000
Decimal         Binary                              Hexadecimal
----------------------------------------------------------------~
x  1            00000000000000000000000000000001   0x00000001
x' 16777216     00000001000000000000000000000000   0x01000000
Decimal         Binary                              Hexadecimal
----------------------------------------------------------------
x  123456789    00000111010110111100110100010101   0x075bcd15
x' 365779719    00010101110011010101101100000111   0x15cd5b07
Decimal         Binary                              Hexadecimal
----------------------------------------------------------------
x  2147483648    10000000000000000000000000000000   0x80000000
x' 128          00000000000000000000000010000000   0x00000080
Decimal         Binary                              Hexadecimal
----------------------------------------------------------------
x  1431655765    01010101010101010101010101010101   0x55555555
x' 1431655765    01010101010101010101010101010101   0x55555555

## Sources used

geeksforgeeks.org

----------