/* Sam Rack
 * Compilers - Parser
 * symbol.c
 */
#include "symbol.h"
#include <string.h>

struct symbol * symbol_create( symbol_t kind, int which, struct type *type, char *name, int funcDefined ) {
	struct symbol *s = malloc(sizeof(*s));
	s->kind = kind;
	s->which = which;
	s->type = type;
	s->funcDefined = funcDefined;

	if (name) {
		s->name = malloc(strlen(name) + 1);
		strcpy(s->name, name);
	}
	return s;
}

