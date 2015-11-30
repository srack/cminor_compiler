/* Sam Rack
 * Compilers
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

/* function:	decl_resolve
 * purpose:	recursive name resolution for declaration tree <d>
 */
void decl_resolve( struct decl *d, struct hash_table **h, int whichSoFar, int shouldPrint) {
	// null check
	if (!d) return;

	// check for second declaration of same name
	struct symbol *sym;
	if (sym = scope_lookup_local(*h, d->name)) {
		if (!sym->funcDefined && d->code) {
			// okay, the funciton was declared already, but this is the definition
			sym->funcDefined = 1;	
			d->symbol = sym;
		}
		else {
			fprintf(stderr, "resolve error: %s is defined again in the same scope\n", d->name);
			++error_count;
			return;	//at this point, we don't want to resolve this decl anymore???
		}
	}
	else {	
		// add the name to the symbol table in the current scope
		if (scope_level(*h) == 1) {
			// we are at global scope
			sym = symbol_create(SYMBOL_GLOBAL, 0, d->type, d->name, (d->code ? 1 : 0));
		} else {
			sym = symbol_create(SYMBOL_LOCAL, whichSoFar, d->type, 0, (d->code ? 1 : 0));
			++whichSoFar;	// another local has been added
		}
		d->symbol = sym;
		scope_bind(*h, d->name, sym);
	}
	
	// resolve the expression, if one exists
	expr_resolve(d->value, *h, shouldPrint);	

	// function declaration
	if (d->code) {
		scope_enter(h);
		param_list_resolve(d->type->params, *h, 0, shouldPrint);
		stmt_resolve(d->code, h, 0, shouldPrint);	// whichSoFar gets reset for each function
		scope_leave(h);	
	}

	// resolve the next decl in the list
	decl_resolve(d->next, h, whichSoFar, shouldPrint);	
}

/* function:	decl_typecheck
 * purpose: 	...
 */
void decl_typecheck( struct decl *d ) {
	if (!d) return;

	// if it is a declaration with an assignment, check the expression vs the type
	// 	of the declaration
	if (d->value) {
		if (d->symbol->kind == SYMBOL_GLOBAL && (d->value->left || d->value->right)) {
			printf("type error: cannot have a non-literal (");
			expr_print(d->value);
			printf(") at the global declaration of %s\n", d->name);
			++error_count;
		}
		else {
			struct type *t = expr_typecheck(d->value);
			if (!type_compare(d->type, t)) {
				printf("type error: cannot assign ");
				type_print(t);
				printf(" (");
				expr_print(d->value);
				printf(") to a declared ");
				type_print(d->type);
				printf("\n");
				++error_count;
			}
		}
	}

	// maybe check if it is global -- then needs to be constant

	// if it is a function declaration, do a typecheck on the code
	// pass in the return type of the declaration to be compared on
	// return statements
	if (d->code) {
		stmt_typecheck(d->code, d);
	}
	decl_typecheck(d->next);
}


/* function:	decl_codegen
 * purpose:
 */
void decl_codegen( struct decl *d, FILE *f ) {


}
