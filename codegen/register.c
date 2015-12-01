/* Sam Rack
 * Compilers
 * register.c
 */

#include "register.h"

// global array to track which registers are free
int regs [16] = { /*rax*/ 1, /*rbx*/ 0, /*rcx*/ 1, /*rdx*/ 1, /*rsi*/ 1, /*rdi*/ 1, /*rbp*/ 1, /*rsp*/ 1, /*r8*/ 1, /*r9*/ 1, /*r10*/ 0, /*r11*/ 0, /*r12*/ 0, /*r13*/ 0, /*r14*/ 0, /*r15*/ 0 };

const char *register_name(int r) {
	switch (r) {
		case 1:
			return "%%rbx";
		case 10:
			return "%%r10";
		case 11:
			return "%%r11";
		case 12:
			return "%%r12";
		case 13:
			return "%%r13";
		case 14:
			return "%%r14";
		case 15:
			return "%%r15";
		default:
			// should not happen, so put in an error message for debugging
			printf("codegen error: asking for invalid register number: %d\n", r);
			exit(1);
	}
}

int register_alloc() {
	int i;
	for (i = 0; i < 16; ++i) {
		if (regs[i] == 0) {
			// allocate this one
			regs[i] = 1;
			return i;
		}
	}
	printf("codegen error: out of registers\n");
	exit(1);
}

void register_free(int r) {
	regs[r] = 0;
}

