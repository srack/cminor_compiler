/* Sam Rack
 * Compilers
 * type.c
 */

#include "type.h"

struct type * type_create( type_kind_t kind, struct param_list *params, struct type *subtype, struct expr *expr ) {
	struct type *t = malloc(sizeof(*t));
	t->kind = kind;
	t->params = params;
	t->subtype = subtype;
	t->expr = expr;
	return t;
}

struct type * type_copy( struct type *t) {
	if (!t) return;

	struct type *copy = malloc(sizeof(*t));
	copy->kind = t->kind;
	copy->params = param_list_copy(t->params);
	copy->subtype = type_copy(t->subtype);
	copy->expr = expr_copy(t->expr);
	return copy;
}

void type_print( struct type *t ) {
	switch(t->kind) {
		case TYPE_BOOLEAN:
			printf("boolean");
			break;
		case TYPE_CHARACTER:
			printf("char");
			break;
		case TYPE_INTEGER:
			printf("integer");
			break;
		case TYPE_STRING:
			printf("string");
			break;
		case TYPE_ARRAY:
			printf("array [");
			expr_print(t->expr);
			printf("] ");
			type_print(t->subtype);
			break;
		case TYPE_FUNCTION:
			printf("function ");
			type_print(t->subtype);
			printf(" (");
			param_list_print(t->params);
			printf(")");
			break;
		case TYPE_VOID:
			printf("void");
			break;
	}
}

/* function:	type_compare
 * purpose:	recursively compares the type of <a> to the type of <b>
 * 		returns 1 if they are the same, otherwise returns 0
 */
int type_compare(struct type * a, struct type * b) {
	// null checks
	if (!a && !b) return 1;
	if (!a || !b) return 0;

	if (a->kind != b->kind) {
		return 0;
	}
	if (!type_compare(a->subtype, b->subtype)) {
		return 0;
	}
	if (!param_list_type_compare(a->params, b->params)) {
		return 0;
	}
	// if it is an array, need to check the expression type
	if (a->kind == TYPE_ARRAY) {
		if (a->expr && a->expr->kind != EXPR_INTEGER_LITERAL) {
			printf("type error: cannot specify array size with a ");			type_print(expr_typecheck(a->expr));
			printf(" (");
			expr_print(a->expr);
			printf(")\n");
			++error_count;
		}	
		else if (b->expr && b->expr->kind != EXPR_INTEGER_LITERAL) {
			printf("type error: cannot specify array size with a ");
			type_print(expr_typecheck(b->expr));
			printf(" (");
			expr_print(b->expr);
			printf(")\n");
			++error_count;
		}
		else if (a->expr && b->expr && a->expr->literal_value != b->expr->literal_value) {
			// sizes of arrays don't match
			printf("type error: array sizes do not match\n");
			++error_count;
		}
	}

	return 1;
}

/* function:	type_delete
 * purpose:	recursively delete the type structure
 */
void type_delete( struct type *t ) {
	if (!t) return;
	
	param_list_delete(t->params);
	expr_delete(t->expr);
	type_delete(t->subtype);		
	// finally, free the root of the type tree
	free(t);
}
