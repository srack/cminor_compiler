/* Sam Rack
 * Compilers
 * shared.c
 */

#include "shared.h"

void printIndent(int indent) {
	int i;
	for (i = 0; i < indent; ++i) {
		printf("\t");
	}
}

void preamble_codegen(FILE *f, int numArgs, int numLocals) {
	// save old rbp
	fprintf(f, "PUSHQ %%rbp\n");
	// update rbp
	fprintf(f, "MOVQ %%rsp, %%rbp\n");

	// save arguments to stack
	if (numArgs > 0) fprintf(f, "PUSHQ %%rdi\n");
	if (numArgs > 1) fprintf(f, "PUSHQ %%rsi\n");
	if (numArgs > 2) fprintf(f, "PUSHQ %%rdx\n");
	if (numArgs > 3) fprintf(f, "PUSHQ %%rcx\n");
	if (numArgs > 4) fprintf(f, "PUSHQ %%r8\n");
	if (numArgs > 5) fprintf(f, "PUSHQ %%r9\n");

	// make space for the locals on the stack
	fprintf(f, "SUBQ $%d, %%rsp\n", numLocals*8);

	// callee saved registers
	fprintf(f, "PUSHQ %%rbx\n");
	fprintf(f, "PUSHQ %%r12\n");
	fprintf(f, "PUSHQ %%r13\n");
	fprintf(f, "PUSHQ %%r14\n");
	fprintf(f, "PUSHQ %%r15\n");
}

void postamble_codegen(FILE *f) {
	// callee saved registers
	fprintf(f, "POPQ %%r15\n");
	fprintf(f, "POPQ %%r14\n");
	fprintf(f, "POPQ %%r13\n");
	fprintf(f, "POPQ %%r12\n");
	fprintf(f, "POPQ %%rbx\n");

	// move rsp to start of function and restore rbp
	fprintf(f, "MOV %%rbp, %%rsp\n");
	fprintf(f, "POPQ %%rbp\n");
	fprintf(f, "RET\n");
}
