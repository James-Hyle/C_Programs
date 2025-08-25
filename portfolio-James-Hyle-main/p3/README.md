# Project #3: List0

* Author: James Hyle
* Class: CS253 Section #001
* Semester: Spring 2025

## Overview

This project has three areas, List.c, String.c and the tests for the data structure. String.c holds a string and its 
length. List.c holds an array of strings, as well as its size and maxsize. The list data structure is this project is 
modeled after an ArrayList, and adding and removal of elements are O(1) operations. The listsort is implemented using 
merge sort.

## Reflection

I had a pretty hard time with this project, although I did learn a lot. The syntax of C has been a large growing pain 
for me, but I am starting to feel a bit more comfortable reading pointers. Memory management wasn't actually the 
hardest part for me, but making sure I am accessing the right 'level' in the data structure. The dereference operator 
'*' is slowly making more sense for me, a video I watched on pointers in C made a good analogy. A variable is a house 
and we want to get it appraised, instead of tearing down the whole house, putting each piece on a truck, and rebuilding 
the house, we give him/her the address of our house and then they can come and do their business. That really helped 
cement the difference between pass by value and pass by reference. 

I am trying to be more deliberate when writing code, because I tend to accrue a lot of technical debt starting 
projects. I spent way too much time looking for an off by one error, that was causing 11 bytes of memory to not be freed
(one string wasn't being removed). I think I would benefit greatly from slowing down my process and taking the time to 
really examine what the project requirements are asking of me. I did end up making a drawing of the chars in a string, 
and then the strings in a list, and that really helped me visualize what is happening internally. I have always 
struggled with the abstraction in Computer Science, but thinking of objects as physical entities helps me define the 
operations. For example, I am glad that I recognized almost right away that adding and removal can be done in constant 
time by accessing the rear of the list. I needed to draw out the operation with each step in the process to complete my 
method to do so, as my first attempt to implement the method was pretty garbage, and contained uneccesary operations. 
Finally, passing valgrind with 10,000 random tests does feel a bit like dining with the heros of old. 

## Compiling and Using

User should first run make to compile project, then choose a test suite to run.
-simple-test
-random-test
require value for test number

-string-test
-list-test
run without input

## Results 

[jameshyle@onyx p3]$ make
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g -D_GNU_SOURCE   -c -o string-test.o string-test.c
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g -D_GNU_SOURCE   -c -o List.o List.c
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g -D_GNU_SOURCE   -c -o String.o String.c
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g -D_GNU_SOURCE -o string-test string-test.o List.o String.o 
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g -D_GNU_SOURCE   -c -o simple-test.o simple-test.c
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g -D_GNU_SOURCE -o simple-test simple-test.o List.o String.o 
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g -D_GNU_SOURCE   -c -o list-test.o list-test.c
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g -D_GNU_SOURCE -o list-test list-test.o List.o String.o 
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g -D_GNU_SOURCE   -c -o random-test.o random-test.c
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g -D_GNU_SOURCE -o random-test random-test.o List.o String.o 
[jameshyle@onyx p3]$ make mem-test-list 
valgrind --leak-check=full --track-origins=yes ./random-test 10000 10000 123
==3933866== Memcheck, a memory error detector
==3933866== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==3933866== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==3933866== Command: ./random-test 10000 10000 123
==3933866== 
Running test #9999
 ========================
 Function  #invocations
 ========================
 ListAppend      1355 
 ListAdd(0)      1426 
 ListRemove      1478 
 ListRemove(0)   1490 
 ListRemove(end) 1394 
 ListSort        1392 
 ListIndexOf     1465 
 ========================
==3933866== 
==3933866== HEAP SUMMARY:
==3933866==     in use at exit: 0 bytes in 0 blocks
==3933866==   total heap usage: 25,802,521 allocs, 25,802,521 frees, 1,364,809,440 bytes allocated
==3933866== 
==3933866== All heap blocks were freed -- no leaks are possible
==3933866== 
==3933866== For lists of detected and suppressed errors, rerun with: -s
==3933866== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

## Sources used

Merge Sort Psuedocode: https://www.mygreatlearning.com/blog/merge-sort/
GeeksforGeeks.org

----------

## Notes

* This README.md template is using Markdown. Here is some help on using Markdown: 
[markdown cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)


* Markdown can be edited and viewed natively in most IDEs such as Eclipse and VS Code. Just toggle
between the Markdown source and preview tabs.

* To preview your README.md output online, you can copy your file contents to a Markdown editor/previewer
such as [https://stackedit.io/editor](https://stackedit.io/editor).