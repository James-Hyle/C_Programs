# Project #: Project Name

* Author: James Hyle
* Class: CS253 Section #001
* Semester: Spring '25

## Overview

This program is a series of text modifiers for the shell environment.
shout           - Capitalize characters of input
whisper         - Uncapitalize characters of input
jn              - Removes newlines
wrp <num>       - Wrap text to a certain limit (num)
cap             - Correct punctuation and capitalization
dedup <char>    - Remove duplicate char from input

## Reflection

This project was difficult, but I also learned a lot in using C and problem solving. I spent the most time on wrp and cap espcially. I had a hard time choosing conditional statements to use, as I am used to java where references are much more easily managed. I am starting to see the differences between C and Java as an object oriented language as well. I am taking CS354 as well and I can also draw connections to functional programming as well, for example, the setbit function in shout and whisper should always either capitalize or decapitalize the input string. I am curious if there is way to easily implement pure functions in C, as I think there is applications in text editing.

Wrp and cap were the hardest programs to implement by far, cap had many decisions to make in keeping track of i while correctly printing the buffer. In cap a specific problem was printing a null char at the end of the file. Because the file ends in a period, my program would overflow, even though I thought I implemented the correct check in I. In java it is much easier to check using built in methods and object references, whereas C requires more modular thinking. I had a few interesting bugs to debug in this project, in cap, I was getting a double free error, I am curous about this as I wonder if my pointer to prevLine is held in the line reference. My line of thinking is that they would be held in seperate memory spaces, but after removing a call to free(prevLine) my program ran and compiled with no errors or warning. Another topic to research it sounds like.

## Compiling and Using

This program requires support of the Posix library for support of the getline function. Usage requires compilation first, and then invocation of program on the command line. User should input text or use file redirection to modify input.

## Results

A foot rheostat is available for
variable speed control. To connect, join
motor cord plug with rheostat plug. See
parts list. Assembly instructions -- the
base and column are assembled together
at the factory, as are also the motor
and table bracket assemblies. Slide the
table bracket assembly first on the
column, position and tighten. The motor
assembly is then slid on the column.
Line up the motor with the table and
tighten temporarily with hand wheel.
Insert drill into chuck and line up
drill with hole in center of table.


## Sources used

man7.org
GNU.org
Stack overflow

----------