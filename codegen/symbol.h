/* Sam Rack
 * Compilers - Parser
 * symbol.h
 * Interface for functions that manage symbol table entries.
 */

#ifndef SYMBOL_H
#define SYMBOL_H

#include "type.h"
#include <string.h>

typedef enum {
	SYMBOL_LOCAL,
	SYMBOL_PARAM,
	SYMBOL_GLOBAL
} symbol_t;


struct symbol {
	symbol_t kind;
	int which;
	struct type *type;
	char *name;
	int funcDefined;
	struct symbol *funcIn;	// symbol for function in which this symbol is
	int numLocals;
};
struct symbol * symbol_create( symbol_t kind, int which, struct type *type, char *name, int funcDefined, struct symbol *funcIn);
char * symbol_code(struct symbol *s);
#endif
