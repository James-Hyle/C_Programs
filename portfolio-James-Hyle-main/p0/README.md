# Project #0: Scavenger Hunt

* Author: James Hyle
* Class: CS253 Section #001
* Semester: Spring 2025

## Overview

This is a small program intended to show my familiarity with the printf function in C. The program will output a series of converted/formatted statements to the console upon excecution.

## Personal Goal

My goal for this semester is to learn C well enough to work on my own projects with microprocessors and low level systems. I am really interested in learning memory management and security, as I have not had any coding projects on those topics yet. A secondary goal I have is to get an 'A' in both this class and ECE330-Microprocessors, as I feel this classes synergize well and I want to get the most benefit from both.


## Results 

[jameshyle@onyx p0]$ git remote -v
origin  https://github.com/Keys-253/portfolio-James-Hyle.git (fetch)
origin  https://github.com/Keys-253/portfolio-James-Hyle.git (push)
[jameshyle@onyx p0]$ make 
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g   -c -o main.o main.c
gcc -Wall -Wextra -Wpointer-arith -Wstrict-prototypes -std=c99 -g main.o -o main
[jameshyle@onyx p0]$ make test
./main
3.141590
G
71
Hello, world!
3.142
+3.14000
1d
35
10      20

107[jameshyle@onyx p0]$ make clean
rm -f *.o *.d *.s a.out main

## Sources used

geeksforgeeks.org

----------