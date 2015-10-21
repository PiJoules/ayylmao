/**
 * AYY LMAO
 * Ayy lmao is essentially a clone of brainfuck, but with the
 * number of commands reduced from 8 characters down to my 5
 * favorite letters in the english alphabet (A,l,m,a,o).
 * 
 * Ayy lmao is represented by an array of N cells initialized 
 * to zero. Each cell is represented by M bits, and any of the
 * 5 operations shown are allowed: A,l,m,a,o.
 * 
 * Operations:
 * A - (operand) flips the operand to work on based on the value
 *     of the switch
 *   0: operate on pointer
 *   1: operate on the value at the pointer
 * l - (operation) perform an operation on the operand
 *   0: increment by 1 (+1)
 *   1: decrement by 1 (-1)
 * m - (operation) either read or print operation
 *   0: print to stdout
 *   1: read from stdin
 * a - (operation) start and end of a while loop
 *   0: If the value at the current cell is zero, skip to the
 *      corresponding 'a'. Otherwise, move to the next 
 *      instruction.
 *   1: If the value at the current cell is zero, move to the 
 *      next instruction. Otherwise, move backwards in the 
 *      instructions to the corresponding 'a'.
 * o - The boolean switch for deciding which operation (l,m,a) 
 *     should be done on the operand (A).
 *
 * An Ayy lmao program is initialized with all cells default
 * to zero. The program counter automatically increments every 
 * iteration. The switch and operand are set to zero by default.
 */

#include <stdio.h>

// Operations
#define OP_END			0
#define OP_INC_DP       1
#define OP_DEC_DP       2
#define OP_INC_VAL      3
#define OP_DEC_VAL      4
#define OP_OUT          5
#define OP_IN           6
#define OP_JMP_FWD      7
#define OP_JMP_BCK      8

// Sizes
#define PROGRAM_SIZE    65536 // 2 bytes
#define STACK_SIZE      65536 // 2 bytes
#define DATA_SIZE       65536 // 2 bytes

// Stack operations
#define STACK_PUSH(A)   (STACK[SP++] = A)
#define STACK_POP()     (STACK[--SP])
#define STACK_EMPTY()   (SP == 0)
#define STACK_FULL()    (SP == STACK_SIZE)

struct instruction_t {
    unsigned short operator;
    unsigned short operand;
};

static struct instruction_t PROGRAM[PROGRAM_SIZE];
static unsigned short STACK[STACK_SIZE];
static unsigned int SP = 0;

int compile(FILE *fp){
	unsigned int c;
	unsigned int pc = 0, jmp_pc;
	int flag = 0, ptr_val = 0;

	while ((c = getc(fp)) != EOF){
		if (c == 'A'){
			ptr_val = !ptr_val;
		}
		else if (c == 'l' || c == 'm' || c == 'a') {
			if (flag){ // Switch is on (1)
				switch (c){
					case 'l': // -1
						if (ptr_val){ // Val
							PROGRAM[pc].operator = OP_DEC_VAL;
						}
						else { // Ptr
							PROGRAM[pc].operator = OP_DEC_DP;
						}
						break;
					case 'm': // read
						PROGRAM[pc].operator = OP_IN;
						break;
					case 'a': // ]
		                if (STACK_EMPTY()) {
		                	fprintf(stderr, "The stack is empty.\n");
		                    return 1;
		                }
		                jmp_pc = STACK_POP();
		                PROGRAM[pc].operator =  OP_JMP_BCK;
		                PROGRAM[pc].operand = jmp_pc;
		                PROGRAM[jmp_pc].operand = pc;
		                break;
				}
			}
			else { // Switch is off (0)
				switch (c){
					case 'l': // +1
						if (ptr_val){ // Val
							PROGRAM[pc].operator = OP_INC_VAL;
						}
						else { // Ptr
							PROGRAM[pc].operator = OP_INC_DP;
						}
						break;
					case 'm': // print
						PROGRAM[pc].operator = OP_OUT;
						break;
					case 'a': // [
		                PROGRAM[pc].operator = OP_JMP_FWD;
		                if (STACK_FULL()) {
		                	fprintf(stderr, "The stack is full.\n");
		                    return 1;
		                }
		                STACK_PUSH(pc);
						break;
				}
			}
			pc++;
		}
		else if (c == 'o'){
			flag = !flag;
		}

		if (pc >= PROGRAM_SIZE-1){
			fprintf(stderr, "The program contians too many characters.\n");
        	return 1;
		}
	}
	if (!STACK_EMPTY()){
		fprintf(stderr, "The stack is not empty. Make sure the number of 'a's equals the number of 'oa's.\n");
    	return 1;
	}

	PROGRAM[pc+1].operator = OP_END;
	return 0;
}

int execute() {
    unsigned short data[DATA_SIZE], pc = 0;
    unsigned int ptr = DATA_SIZE;
    while (--ptr) { data[ptr] = 0; }
    while (PROGRAM[pc].operator != OP_END && ptr < DATA_SIZE) {
        switch (PROGRAM[pc].operator) {
            case OP_INC_DP: ptr++; break;
            case OP_DEC_DP: ptr--; break;
            case OP_INC_VAL: data[ptr]++; break;
            case OP_DEC_VAL: data[ptr]--; break;
            case OP_OUT: putchar(data[ptr]); break;
            case OP_IN: data[ptr] = (unsigned int)getchar(); break;
            case OP_JMP_FWD: if(!data[ptr]) { pc = PROGRAM[pc].operand; } break;
            case OP_JMP_BCK: if(data[ptr]) { pc = PROGRAM[pc].operand; } break;
            default: return 1;
        }
        pc++;
    }
    return ptr != DATA_SIZE;
}

int main(int argc, const char *argv[]){
	if (argc != 2){
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		return 1;
	}

	FILE *fp = (FILE*)fopen(argv[1], "r");
	if (fp == NULL){
		fprintf(stderr, "Could not read file %s\n", argv[1]);
		return 1;
	}
	if (compile(fp)){
		return 1;
	}
	else {
		return execute();
	}

	return 0;
}