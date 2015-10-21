#include <stdio.h>

/*

A bf to ayy lmao interpretter. Reads bf from stdin and prints
ayy lmao to stdout.

A simple way to transl8 is to always revert the state of the
program back to defaults after changing them. This way, after
each command, you know you will be working with A == 0 and 
o == 0. Therefore, the number of 'A's and 'o's in the ayy lmao 
program should each be even.

Keeping track of the state each time could reduce the amount of
unecessary 'o's and 'A's if the state will be constant for a string
of commands, so this will have to be done l8r.

ayy lmao 	bf
l 	  		> 	Increment the pointer.
olo			< 	Decrement the pointer.
AlA			+ 	Increment the byte at the pointer.
AolAo		- 	Decrement the byte at the pointer.
m			. 	Output the byte at the pointer.
omo			, 	Input a byte and store it in the byte at the pointer.
a			[ 	Jump forward past the matching ] if the byte at the pointer is zero.
oao			] 	Jump backward to the matching [ unless the byte at the pointer is zero.

 */

int main(int argc, const char *argv[]){
	char c;
	while ((c = getchar()) != EOF){
		switch (c){
			case '>': printf("l"); break;
			case '<': printf("olo"); break;
			case '+': printf("AlA"); break;
			case '-': printf("AolAo"); break;
			case '.': printf("m"); break;
			case ',': printf("omo"); break;
			case '[': printf("a"); break;
			case ']': printf("oao"); break;
		}
	}

	return 0;
}