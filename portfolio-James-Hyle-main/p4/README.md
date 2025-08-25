# Project #: Generic List and myls

* Author: James Hyle
* Class: CS253 Section #001
* Semester: Spring 2025


## Overview

This program contains modules for a generic list and an a algorithm based on the 'ls' command to display files and their information contained in an
environment. The List source file utilizes an array of void pointers to store elements of any type inside, and is modeled on an arraylist data structure,
allowing O(1) addition and removal of elements. The list uses function pointers for methods to provide functionality for comparison, writing string
representation, and destroying the generic object. The List also uses a filter function in its print method to decide whether an element should be displayed.

myls uses the POSIX library system calls to safely gather files and their information into a list. The user can choose to
manipulate the list to display the files by directory only, file size, time file last modified, or alphabetically by default.
The program organizes the information into file-info objects which are the actual entries inside the generic list.


## Reflection

I had a good time with this project. I enjoyed learning about the different system calls and data fields interfacing with my
files, and seeing the project files pop up just like using ls was really really cool. Code portability has always been a
strange and esoteric topic for me, it blows my mind that we get all the functionality across so many systems. Reading on the
POSIX interface helped me understand a few things I have been curious about. In ECE330 - Microprocessors, some of the c code
we worked with made a reference to 'size_t', and I just kept wondering where the heck that little underscore t meant, where
it came from, and what its intentions are. I stumbled upon the definition of the variable on the GNU.opg website (https://www.
gnu.org/software/libc/manual/html_node/Important-Data-Types.html), and was enlightened, it is an integer type reserved for
the size of objects. Of course, I had gleaned that size_t had something to do with object size, but seeing the documentation
defining the variable and its usage is helping me see how all these different aspects of software engineering come together.

The organization we briefly mentioned in lecture, ISO, the same organization that defines bolt and washer tolerances, also
defines C standards, which completely blew my mind. I worked in construction before coming back to school, and I take
software architecture quite literally. Reading through code documentation is incredibly similar to parsing technical
documents specifying not only the materials for a fixture or workpiece, but the proper methodology for installation and use.
C makes more sense to me framing it in a construction project, and reading the standards is putting many aspects of
programming in context. In a very real sense to me, primitive types are like 2x4, bolts, or other hardware we can put
together to form complex, functional, and hopefully sturdy programs. Standards for bolts, materials, and code are critical
pieces of our infrastructure, and without creating these standards, we'd have a lot more building collapses, car accidents,
and software crashes to deal with. Granted, the standards are not enforced, however, organizations where source code build
quality truly matters, such as NASA, have incredibly stringent code standards they adhere to. One of my favorite videos on
youtube is about the 'first' microprocessor, the F-14 Tomcat CADC or Central Air Data Computer, held just 128 20-bit words,
or about 2.5kb. A single bit could not be off or mistaken, especially when the pilot's life is at stake.    


## Compiling and Using

Users should invoke make "file-name" to compile files and dependencies, alternatively can invoke 'make all'. There are two modules demonstrating list and 'ls'
functionality, simple-test and myls. Simple-test requires an integer value for the number of dummy entries to input, and myls requires a valid directory to peruse
through. User can set flags in myls: -D for show directories only, -s to sort entries by file size, -t to sort by last modified time. -d is a required default
argument flag for the path of directory to list.


## Results

[jameshyle@onyx p4]$ make
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g -D_GNU_SOURCE List.c -c -o List.o
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g -D_GNU_SOURCE   -c -o myls.o myls.c
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g -D_GNU_SOURCE   -c -o file-info.o file-info.c
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g -D_GNU_SOURCE List.o myls.o file-info.o -o myls
[jameshyle@onyx p4]$ make simple-test
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g -D_GNU_SOURCE   -c -o simple-test.o simple-test.c
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g -D_GNU_SOURCE simple-test.o List.o file-info.o -o simple-test
[jameshyle@onyx p4]$ ./simple-test 10
dummy file #0         1024      Wed Dec 31 17:00:00 1969
dummy file #1         1025      Wed Dec 31 17:00:00 1969
dummy file #2         1026      Wed Dec 31 17:00:00 1969
dummy file #3         1027      Wed Dec 31 17:00:00 1969
dummy file #4         1028      Wed Dec 31 17:00:00 1969
dummy file #5         1029      Wed Dec 31 17:00:00 1969
dummy file #6         1030      Wed Dec 31 17:00:00 1969
dummy file #7         1031      Wed Dec 31 17:00:00 1969
dummy file #8         1032      Wed Dec 31 17:00:00 1969
dummy file #9         1033      Wed Dec 31 17:00:00 1969
dummy file #9         1033      Wed Dec 31 17:00:00 1969
dummy file #8         1032      Wed Dec 31 17:00:00 1969
dummy file #7         1031      Wed Dec 31 17:00:00 1969
dummy file #6         1030      Wed Dec 31 17:00:00 1969
dummy file #5         1029      Wed Dec 31 17:00:00 1969
dummy file #4         1028      Wed Dec 31 17:00:00 1969
dummy file #3         1027      Wed Dec 31 17:00:00 1969
dummy file #2         1026      Wed Dec 31 17:00:00 1969
dummy file #1         1025      Wed Dec 31 17:00:00 1969
dummy file #0         1024      Wed Dec 31 17:00:00 1969
[jameshyle@onyx p4]$ myls -d . -s
Project 4_ Generic List.pdf         123249      Fri Apr  4 09:31:24 2025
myls                 42904      Thu Apr 17 13:47:35 2025
simple-test          33864      Thu Apr 17 13:47:44 2025
myls.o               13136      Thu Apr 17 13:47:35 2025
List.o               12888      Thu Apr 17 13:47:35 2025
file-info.o          10632      Thu Apr 17 13:47:35 2025
simple-test.o         8544      Thu Apr 17 13:47:44 2025
List.c                5608      Thu Apr 17 11:57:01 2025
.                     4096      Thu Apr 17 13:47:44 2025
myls.c                2890      Wed Apr 16 22:31:10 2025
List.h                2533      Wed Apr 16 20:16:44 2025
file-info.h           2096      Wed Apr 16 10:04:20 2025
file-info.c           1963      Wed Apr 16 20:34:52 2025
rubric.txt            1094      Thu Apr  3 12:00:11 2025
README.md             1015      Thu Apr 17 11:54:52 2025
simple-test.c          669      Wed Apr 16 20:23:27 2025
Makefile               360      Sun Apr  6 21:28:11 2025
..                     172      Fri Feb  7 21:38:05 2025
.gitkeep                 0      Sun Jan 19 07:13:39 2025
[jameshyle@onyx p4]$ myls -t -d .
.gitkeep                 0      Sun Jan 19 07:13:39 2025
..                     172      Fri Feb  7 21:38:05 2025
rubric.txt            1094      Thu Apr  3 12:00:11 2025
Project 4_ Generic List.pdf         123249      Fri Apr  4 09:31:24 2025
Makefile               360      Sun Apr  6 21:28:11 2025
file-info.h           2096      Wed Apr 16 10:04:20 2025
List.h                2533      Wed Apr 16 20:16:44 2025
simple-test.c          669      Wed Apr 16 20:23:27 2025
file-info.c           1963      Wed Apr 16 20:34:52 2025
myls.c                2890      Wed Apr 16 22:31:10 2025
README.md             1015      Thu Apr 17 11:54:52 2025
List.c                5608      Thu Apr 17 11:57:01 2025
List.o               12888      Thu Apr 17 13:47:35 2025
myls.o               13136      Thu Apr 17 13:47:35 2025
file-info.o          10632      Thu Apr 17 13:47:35 2025
myls                 42904      Thu Apr 17 13:47:35 2025
.                     4096      Thu Apr 17 13:47:44 2025
simple-test.o         8544      Thu Apr 17 13:47:44 2025
simple-test          33864      Thu Apr 17 13:47:44 2025
[jameshyle@onyx p4]$ myls -D -d ..
.                      172      Fri Feb  7 21:38:05 2025
..                     108      Sat Feb 22 17:35:55 2025
.git                  4096      Wed Apr 16 20:25:21 2025
.vscode                113      Fri Feb 21 23:02:33 2025
p0                     192      Fri Feb 14 11:49:25 2025
p1                     192      Sat Feb 15 07:45:16 2025
p2                    4096      Sun Mar  2 23:15:24 2025
p3                    4096      Mon Mar 31 20:02:40 2025
p4                    4096      Thu Apr 17 13:47:44 2025
p5                      30      Sun Jan 19 07:13:40 2025


## Sources used

man7.org
man.openbsd.org
gnu.org