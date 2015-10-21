#include <stdio.h>

/*

An ayy lmao to bf interpretter. Reads ayy lmap from stdin and 
prints bf to stdout.

 */

int main(int argc, const char *argv[]){
	int flag = 0, operand = 0;
	char c;
	while ((c = getchar()) != EOF){
		if (c == 'A'){
			operand = !operand;
		}
		else if (c == 'l' || c == 'm' || c == 'a') {
			if (flag){ // Switch is on (1)
				switch (c){
					case 'l': // -1
						if (operand){ // Val
							printf("-");
						}
						else { // Ptr
							printf("<");
						}
						break;
					case 'm': // read
						printf(",");
						break;
					case 'a': // ]
		                printf("]");
		                break;
				}
			}
			else { // Switch is off (0)
				switch (c){
					case 'l': // +1
						if (operand){ // Val
							printf("+");
						}
						else { // Ptr
							printf(">");
						}
						break;
					case 'm': // print
						printf(".");
						break;
					case 'a': // [
						printf("[");
						break;
				}
			}
		}
		else if (c == 'o'){
			flag = !flag;
		}
	}

	return 0;
}