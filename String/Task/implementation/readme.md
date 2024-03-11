# Author
Nagy Botond-Vilmos

# Description
This folder contains the solution for the the [task](../task.md).

# Content
- `str_bm.h`
header file for the data structure and the functions
- `str_bm.cpp`
implementation of the data structure and the functions
- `text.h`
declaration of helper data structure `text` for easier manipulation of large texts
- `text.cpp`
implementation of the helper data structure `text`
- `grep.cpp`
implementation of the `grep` linux command
- `sgrep.cpp`
implementation of the grep command, but with naive string search algorithm
- `run.sh`
script to run (or just compile) programs
- `test folder`
contains the compiled grep funtion and a reasonably large text file to test the programs

# Compilation
To compile the programs, run the `run.sh` script in the terminal with the following command:
```bash
./run.sh -c grep.cpp str_bm.cpp text.cpp
./run.sh -c sgrep.cpp str_bm.cpp text.cpp
```

# Usage
To test the program, first run it with the '-h' flag to see the usage:
```bash
./grep -h
```
The two programs function the same way, the only difference is the search algorithm used. The `grep` program uses the Boyer-Moore algorithm, while the `sgrep` program uses the naive string search algorithm.

# Testing
The best way to test the true power of the Boyer-Moore algorithm and to compare it to the naive string search algorithm is to type `time` before the command to see the time it takes to run the program.

# Example
Enter the test folder and run the following commands:
```bash
time ./grep <-p{Abraham}> <-f{bible.txt}>
time ./sgrep <-p{Abraham}> <-f{bible.txt}>
```

# Notes
The `grep` program is much faster than the `sgrep` program, especially when searching for longer strings in large texts.
My implementation of the Boyer-Moore algorithm is not the most efficient, but it is still much faster than the naive string search algorithm.
I hope you enjoy using the programs!