/* Sam Rack
 * Compilers - Parser
 * decl.c
 */

#include "decl.h"

struct decl * decl_create( char *name, struct type *t, struct expr *v, struct stmt *c, struct decl *next ) {
	struct decl *d = malloc(sizeof(*d));
	d->name = name;
	d->type = t;
	d->value = v;
	d->code = c;
	d->next = next;
	return d;
}

void decl_print( struct decl *d, int indent ) {
	if (!d) return;

	printIndent(indent);
	printf("%s: ", d->name);
	type_print(d->type);

	// function declaration
	if (d->code) {
		printf(" = {\n");
		stmt_print(d->code, indent+1, 0);
		printIndent(indent);
		printf("}");
	}
	// variable with initializer
	else if (d->value) {
		printf(" = ");
		expr_print(d->value);
		printf(";");
	}
	// variable declaration
	else {
		printf(";");
	}
	printf("\n");
	decl_print( d->next, indent);
}

