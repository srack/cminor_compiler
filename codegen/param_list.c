/* Sam Rack
 * Compilers
 * param_list.c
 */
#include "param_list.h"

struct param_list * param_list_create( char *name, struct type *type, struct param_list *next ) {
	struct param_list *p = malloc(sizeof(*p));
	p->name = malloc(strlen(name) + 1);
	strcpy(p->name,name);
	p->type = type;
	p->next = next;
	return p;
}

struct param_list * param_list_copy( struct param_list *p) {
	if (!p) return NULL;

	struct param_list *copy = malloc(sizeof(*p));
	copy->name = malloc(strlen(p->name) + 1); 
	strcpy(copy->name, p->name);
	copy->type = type_copy(p->type);
	copy->next = param_list_copy(p->next);

	return copy;
}

void param_list_print( struct param_list *p ) {
	if (!p) return;
	printf("%s: ", p->name);
	type_print(p->type);
	if (p->next) {
		printf(", ");
		param_list_print(p->next);
	}
}

/* function:	param_list_resolve
 * purpose:	name resolution for parameter list of a function declaraion
 */
void param_list_resolve( struct param_list *p, struct hash_table *h, int whichSoFar, int shouldPrint) {
	// null check
	if (!p) return;

	// check for second declaration of same name
	if (scope_lookup_local(h, p->name)) {
		fprintf(stderr, "resolve error: %s is defined again in the same scope\n", p->name);
		++error_count;
		return; //at this point, we don't want to resolve this anymore??
	}

	// add the name to the symbol table in the current scope
	struct symbol *sym = symbol_create(SYMBOL_PARAM, whichSoFar, p->type, 0, 0, 0);
	++whichSoFar;
	scope_bind(h, p->name, sym);

	// resolve the next parameter in the list
	param_list_resolve(p->next, h, whichSoFar, shouldPrint);
}

/* function:	param_list_compare
 * purpose:	compares two parameter lists <a> and <b> to check if their 
 * 		types are equivalent
 */
int param_list_type_compare( struct param_list *a, struct param_list *b ) {
	// null checks
	if (!a && !b) {
		return 1;
	} 
	if (!a || !b) {
		return 0;
	}

	if (!type_compare(a->type, b->type)) {
		return 0;
	}
	return param_list_type_compare(a->next, b->next);


}

/* function:	param_list_delete
 * purpose:	deletes all elements in the param_list structure <p>
 */
void param_list_delete( struct param_list *p ) {
	if (!p) return;
	param_list_delete(p->next);
	if (p->name) free(p->name);
	free(p);
}

/* function:	param_list_typecheck
 * purpose:	compares the types of the expressions in <e_list> to the 
 * 		types specified by the parameter list
 *		only returns 0 or 1 because want the error message to happen
 *		at the height of the function call expression
 */
int param_list_typecheck( struct expr *e_list, struct param_list *p) {
	if (!e_list && !p) return 1;
	if (!e_list || !p) return 0; 
	if (!type_compare(expr_typecheck(e_list), p->type)) return 0;
	return param_list_typecheck(e_list->next, p->next);
}
