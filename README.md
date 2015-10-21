# Ayy lmao
Ayy lmao is essentially a clone of brainfuck, but with the number of commands reduced from 8 characters down to my 5 favorite letters in the english alphabet `(A,l,m,a,o)`.

## Why?
Ayy lmao is represented by an array of N cells initialized 
to zero. Each cell is represented by M bits, and any of the
5 operations shown are allowed: A,l,m,a,o.

## Operations
A - (operand) flips the operand to work on based on the value
    of the switch
  0: operate on pointer
  1: operate on the value at the pointer

l - (operation) perform an operation on the operand
  0: increment by 1 (+1)
  1: decrement by 1 (-1)

m - (operation) either read or print operation
  0: print to stdout
  1: read from stdin

a - (operation) start and end of a while loop
  0: If the value at the current cell is zero, skip to the
     corresponding 'a'. Otherwise, move to the next 
     instruction.
  1: If the value at the current cell is zero, move to the 
     next instruction. Otherwise, move backwards in the 
     instructions to the corresponding 'a'.

o - The boolean switch for deciding which operation (l,m,a) 
    should be done on the operand (A).

## What?
An Ayy lmao program is initialized with all cells default
to zero. The program counter automatically increments every 
iteration. The switch and operand are set to zero by default.

## Examples
First compile
```sh
$ gcc ayy.c -o ayy
```

Print out the character 'a'.
```sh
$ ./ayy a.lmao
A
```

Read a character from stdin and print it out
```sh
$ echo A ./ayy a.lmao
A
```

Multiply 2 numbers
```sh
$ echo 11 | ./ayy multiply.lmao
a
```
