# Project #: myps

* Author: James Hyle
* Class: CS253 Section #001
* Semester: Spring 2025

## Overview

This program is a tool for showing information about processes running on a computer system, 
simlar to the command 'ps'. This program looks inside the /proc directory on a linux system 
and iterates through each numbered process id, gathering information from seven fields as it 
traverses. These fields are as follows: 
    
    PID: Process id.
    PPID: Parent Process id.
    STATE: Char descriptor of process. 
    UTIME: The amount of time that the process has been scheduled in user mode.
    STIME: The amount of time that the process has been scheduled in kernel mode.
    THREADS: The number of threads used by by this process.
    CMD: The filename of the executable.
    STAT_FILE: Path.

The program will print to standard output the parsed fields of each entry. 

## Reflection

This project went pretty well for me. I had a hard time initially figuring out what exactly to do according to
the project specifications, but once I had a better understanding of the program, and where I needed to go in
the file system I was able to make much more progress. I followed many of the patterns we used in project 4 as well, 
and a lot of the code for that translated well this program. A key issue I was running into was matching the comm
field of the entry the option -s optarg. I tried a couple of ways of removing the parentheses, but it was much
easier to just wrap the passed in argument with parentheses. In hindsight this was an easy fix, but I spent
a bit of time overthinking the issue. 

I really enjoyed testing the tool and it felt a little bit like a scavenger hunt, tracking down the stray processes.
I am not very familiar with systems programming, but after taking this class I feel like I am ready to take CS452,
Operating Systems, or at least learn more about processes, forking and exec, and larger programs in the C language.
I think C is a really cool language, as mentioned in class, interfacing close to the hardware is really cool and
rewarding. After spending time with the C language, I think that memory management is not too terrible. I think a
lot of people really tend to exaggerate how difficult it is, and I have a limited scope having only developed smaller
program, but keeping track of dynamic memory has not been so much of a challenge for me. Valgrind is a huge help in
plugging memory leaks, and I am glad I got to know the program decently well. Overall I feel like I developed good
working habits and patterns from this class, and I learned a ton about a lot of topics in computer science I have been
really curious about. Thank you for the great semester!
 

## Compiling and Using

User should invoke make commmand to build program and dependencies. 

Usage: ./myps [-s <command>] [-p] [-c] [-z] [-h]

    -s <command>  Display proc entries that match command.
    -p            Display proc entries sorted by pid .
    -c            Display proc entries sorted by command lexicographically.
    -z            Display proc entries in the zombie state.
    -h            Display help message.

## Results 

[jameshyle@onyx p5]$ make clean
/bin/rm -f myps orphan zombie daemon proc-entry-test *.o a.out *.d
[jameshyle@onyx p5]$ make 
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g   -c -o List.o List.c
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g   -c -o myps.o myps.c
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g   -c -o ProcEntry.o ProcEntry.c
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g List.o myps.o ProcEntry.o -o myps
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g   -c -o orphan.o orphan.c
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g orphan.o -o orphan
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g   -c -o zombie.o zombie.c
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g zombie.o -o zombie
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g   -c -o daemon.o daemon.c
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g daemon.o -o daemon
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g   -c -o proc-entry-test.o proc-entry-test.c
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g proc-entry-test.o ProcEntry.o -o proc-entry-test
[jameshyle@onyx p5]$ valgrind --leak-check=full ./myps -p >> test
==3366065== Memcheck, a memory error detector
==3366065== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==3366065== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==3366065== Command: ./myps -p
==3366065== 
==3366065== 
==3366065== HEAP SUMMARY:
==3366065==     in use at exit: 0 bytes in 0 blocks
==3366065==   total heap usage: 10,594 allocs, 10,594 frees, 2,246,205 bytes allocated
==3366065== 
==3366065== All heap blocks were freed -- no leaks are possible
==3366065== 
==3366065== For lists of detected and suppressed errors, rerun with: -s
==3366065== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

[jameshyle@onyx p5]$ valgrind --leak-check=full ./myps -c >> test
==3366162== Memcheck, a memory error detector
==3366162== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==3366162== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==3366162== Command: ./myps -c
==3366162== 
==3366162== 
==3366162== HEAP SUMMARY:
==3366162==     in use at exit: 0 bytes in 0 blocks
==3366162==   total heap usage: 10,594 allocs, 10,594 frees, 2,246,485 bytes allocated
==3366162== 
==3366162== All heap blocks were freed -- no leaks are possible
==3366162== 
==3366162== For lists of detected and suppressed errors, rerun with: -s
==3366162== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

[jameshyle@onyx p5]$ valgrind --leak-check=full ./myps -z
==3366202== Memcheck, a memory error detector
==3366202== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==3366202== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==3366202== Command: ./myps -z
==3366202== 
    PID    PPID STATE UTIME STIME THREADS CMD                       STAT_FILE           
1113703 1113702     Z     0     0       1 (zombie)                  /proc/1113703/stat  
4036344 4036343     Z     0     0       1 (zombie)                  /proc/4036344/stat  
4101457 4101456     Z     0     0       1 (zombie)                  /proc/4101457/stat  
==3366202== 
==3366202== HEAP SUMMARY:
==3366202==     in use at exit: 0 bytes in 0 blocks
==3366202==   total heap usage: 8,676 allocs, 8,676 frees, 2,057,472 bytes allocated
==3366202== 
==3366202== All heap blocks were freed -- no leaks are possible
==3366202== 
==3366202== For lists of detected and suppressed errors, rerun with: -s
==3366202== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

## Orphan
[jameshyle@onyx p5]$ ./orphan
[jameshyle@onyx p5]$ ./myps -s orphan
    PID    PPID STATE UTIME STIME THREADS CMD                       STAT_FILE           
  95373       1     S     0     0       1 (orphan)                  /proc/95373/stat    
 130486       1     S     0     0       1 (orphan)                  /proc/130486/stat   
1112693       1     S     0     0       1 (orphan)                  /proc/1112693/stat  
1145832       1     S     0     0       1 (orphan)                  /proc/1145832/stat  
1145910       1     S     0     0       1 (orphan)                  /proc/1145910/stat  
1216849       1     S     0     0       1 (orphan)                  /proc/1216849/stat  
1790764       1     S     0     0       1 (orphan)                  /proc/1790764/stat  
2033396       1     S     0     0       1 (orphan)                  /proc/2033396/stat  
2037472       1     S     0     0       1 (orphan)                  /proc/2037472/stat  
2049127       1     S     0     0       1 (orphan)                  /proc/2049127/stat  
2432101       1     S     0     0       1 (orphan)                  /proc/2432101/stat  
2447585       1     S     0     0       1 (orphan)                  /proc/2447585/stat  
2929060       1     S     0     0       1 (orphan)                  /proc/2929060/stat  
3209134       1     S     0     0       1 (orphan)                  /proc/3209134/stat  
3363218       1     S     0     0       1 (orphan)                  /proc/3363218/stat  
4003737       1     S     0     0       1 (orphan)                  /proc/4003737/stat  
4113548       1     S     0     0       1 (orphan)                  /proc/4113548/stat  
4114814       1     S     0     0       1 (orphan)                  /proc/4114814/stat  

## Zombie
[jameshyle@onyx p5]$ ./zombie &
[1] 3366329
[jameshyle@onyx p5]$ ./myps -s zombie
    PID    PPID STATE UTIME STIME THREADS CMD                       STAT_FILE           
1113702 1035636     S     0     0       1 (zombie)                  /proc/1113702/stat  
1113703 1113702     Z     0     0       1 (zombie)                  /proc/1113703/stat  
3366329 3363922     S     0     0       1 (zombie)                  /proc/3366329/stat  
3366331 3366329     Z     0     0       1 (zombie)                  /proc/3366331/stat  
4036343       1     S     0     0       1 (zombie)                  /proc/4036343/stat  
4036344 4036343     Z     0     0       1 (zombie)                  /proc/4036344/stat  
4101456       1     S     0     0       1 (zombie)                  /proc/4101456/stat  
4101457 4101456     Z     0     0       1 (zombie)                  /proc/4101457/stat  
[jameshyle@onyx p5]$ kill -9 3366329
[1]+  Killed                  ./zombie
[jameshyle@onyx p5]$ ./myps -s zombie
    PID    PPID STATE UTIME STIME THREADS CMD                       STAT_FILE           
1113702 1035636     S     0     0       1 (zombie)                  /proc/1113702/stat  
1113703 1113702     Z     0     0       1 (zombie)                  /proc/1113703/stat  
4036343       1     S     0     0       1 (zombie)                  /proc/4036343/stat  
4036344 4036343     Z     0     0       1 (zombie)                  /proc/4036344/stat  
4101456       1     S     0     0       1 (zombie)                  /proc/4101456/stat  
4101457 4101456     Z     0     0       1 (zombie)                  /proc/4101457/stat


## Sources used

geeksforgeeks.org
https://man7.org/linux/man-pages/man3/strcasestr.3.html
https://man7.org/linux/man-pages/man3/fopen.3.html

----------