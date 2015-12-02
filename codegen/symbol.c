/* Sam Rack
 * Compilers
 * symbol.c
 */

#include "symbol.h"

struct symbol * symbol_create( symbol_t kind, int which, struct type *type, char *name, int funcDefined, struct symbol *funcIn ) {
	struct symbol *s = malloc(sizeof(*s));
	s->kind = kind;
	s->which = which;
	s->type = type;
	s->funcDefined = funcDefined;
	s->funcIn = funcIn;

	if (name) {
		s->name = malloc(strlen(name) + 1);
		strcpy(s->name, name);
	}
	return s;
}

/* function:	symbol_code
 * purpose:	returns the string corresponding to the code that should
 * 		be used for the symbol <s> during code generation
 * 		NOTE: callee should free the pointer returned after its use
 */
char * symbol_code(struct symbol *s) {
	// if global, just return the name
	if (s->kind == SYMBOL_GLOBAL) {
		// return a copy of the name so it can be freed in the same
		//  way as the params and locals are
		char *buffer = malloc(sizeof(char)*(strlen(s->name)+1));
		strcpy(buffer, s->name);
		return buffer;
	}

	// if a parameter, then is (paramNum+1)*-8 offset from rbp
	else if (s->kind == SYMBOL_PARAM) {
		char *buffer = malloc(sizeof(char)*32);
		sprintf(buffer, "%d(%%rbp)\0", -8*(s->which+1));
		return buffer;
	}

	// if it is a local, then -(totalArgs*8 + (localNum+1)*8) is the offset
	else {
		// figure how many total parameters there are in the current function
		int totalParams = 0;

		// if it is a local, then it will have a non-null funcIn member
	/*	struct param_list *p = s->funcIn->type->params;
		while(p) {
			++totalParams;
			p = p->next;
		}

		char *buffer = malloc(sizeof(char)*32);
		sprintf(buffer, "%d(%%rbp)\0", -8*(totalParams + s->which + 1));
		return buffer;
	*/}

}
