/* Sam Rack
 * Compilers - Parser
 * expr.c
 */
#include "expr.h"
#include <string.h>

int string_literal_count = 0;
extern int jump_label_count;

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right ) {
	struct expr *e = malloc(sizeof(*e));
	e->next = 0;
	e->kind = kind;
	e->left = left;
	e->right = right;
	return e;
}

struct expr * expr_create_name( const char *n ) {
	struct expr *e = expr_create(EXPR_NAME, 0, 0);
	e->name = malloc(sizeof(strlen(n) + 1));
	strcpy(e->name, n);
	return e;
}

struct expr * expr_create_boolean_literal( int c ) {
	struct expr *e = expr_create(EXPR_BOOLEAN_LITERAL, 0, 0);
	e->literal_value = c;
	return e;
}

struct expr * expr_create_integer_literal( int c ) {
	struct expr *e = expr_create(EXPR_INTEGER_LITERAL, 0, 0);
	e->literal_value = c;
	return e;
}

struct expr * expr_create_character_literal( int c ) {
	struct expr *e = expr_create(EXPR_CHARACTER_LITERAL, 0, 0);
	e->literal_value = c;
	return e;
}

struct expr * expr_create_string_literal( const char *str ) {
	struct expr *e = expr_create(EXPR_STRING_LITERAL, 0, 0);
	e->string_literal = malloc(strlen(str) + 1);
	strcpy(e->string_literal, str);
	return e;
}

struct expr * expr_create_function_call( const char *n, struct expr *args ) {
	struct expr *e = expr_create(EXPR_FUNCTION_CALL, args, 0);
	e->name = malloc(sizeof(strlen(n) + 1));
	strcpy(e->name, n);
	return e;
}

struct expr * expr_copy( struct expr *e ) {
	if (!e) return NULL;

	struct expr *copy = malloc(sizeof(*copy));
	copy->kind = e->kind;
	copy->left = expr_copy(e->left);
	copy->right = expr_copy(e->right);
	if (e->name) {
		copy->name = malloc(strlen(e->name)+1);
		strcpy(copy->name, e->name);
	}
	copy->symbol = e->symbol;
	copy->literal_value = e->literal_value;
	if (e->string_literal) {
		copy->string_literal = malloc(strlen(e->string_literal)+1);
		strcpy(copy->string_literal, e->string_literal);
	}
	copy->next = e->next; 

	return copy;
}

void expr_print( struct expr * e ) {
	if (!e) return;
	int i, j;
	char c;
	char *charLit;
	char *strLit;
	switch(e->kind) {
		case EXPR_NAME:
			printf("%s", e->name);
			break;
		case EXPR_INTEGER_LITERAL:
			printf("%d", e->literal_value);
			break;
		case EXPR_STRING_LITERAL:
			// max length of the "extended" string is double the original (where all characters are escaped

			strLit = malloc(sizeof(char) * strlen(e->string_literal) * 2 + 1);
			for (i = 0, j = 0; i < strlen(e->string_literal); ++i, ++j) {
				c = e->string_literal[i];
				if (c == '\a') {
					strLit[j] = '\\';
					++j;
					strLit[j] = 'a';
				} else if (c == '\b') { 
					strLit[j] = '\\';
					++j;
					strLit[j] = 'b';
				} else if (c == '\f') {
					strLit[j] = '\\';
					++j;
					strLit[j] = 'f';
				} else if (c == '\n') {
					strLit[j] = '\\';
					++j;	
					strLit[j] = 'n';
				} else if (c == '\r') {
					strLit[j] = '\\';
					++j;
					strLit[j] = 'r';
				} else if (c == '\t') {
					strLit[j] = '\\';
					++j;
					strLit[j] = 't';
				} else if (c == '\v') {
					strLit[j] = '\\';
					++j;
					strLit[j] = 'v';
				} else if (c == '\"') {
					strLit[j] = '\\';
					++j;
					strLit[j] = '\"';
				} else if (c == '\\') {
					strLit[j] = '\\';
					++j;
					strLit[j] = '\\';
				} else if (c == '\'') {
					strLit[j] = '\\';
					++j;
					strLit[j] = '\'';
				} else if (c == '\?') {
					strLit[j] = '\\';
					++j;
					strLit[j] = '\?'; 
				} else {
					strLit[j] =  e->string_literal[i];
				}
			}
			strLit[j] = '\0';
			printf("\"%s\"", strLit);
			free(strLit);
			break;
		case EXPR_CHARACTER_LITERAL:
			// max size of string to be printed for the character is 3 (including null term)
			charLit = malloc(sizeof(char)*3);
			c = (char)e->literal_value;			
			if (c == '\a') { charLit[0] = '\\'; charLit[1] = 'a'; charLit[2] = '\0'; }
			else if (c == '\b') { charLit[0] = '\\'; charLit[1] = 'b'; charLit[2] = '\0'; }
			else if (c == '\f') { charLit[0] = '\\'; charLit[1] = 'f'; charLit[2] = '\0'; }
			else if (c == '\n') { charLit[0] = '\\'; charLit[1] = 'n'; charLit[2] = '\0'; }
			else if (c == '\r') { charLit[0] = '\\'; charLit[1] = 'r'; charLit[2] = '\0'; }
			else if (c == '\t') { charLit[0] = '\\'; charLit[1] = 't'; charLit[2] = '\0'; }
			else if (c == '\v') { charLit[0] = '\\'; charLit[1] = 'v'; charLit[2] = '\0'; }
			else if (c == '\"') { charLit[0] = '\\'; charLit[1] = '\"'; charLit[2] = '\0'; }
			else if (c == '\\') { charLit[0] = '\\'; charLit[1] = '\\'; charLit[2] = '\0'; }
			else if (c == '\'') { charLit[0] = '\\'; charLit[1] = '\''; charLit[2] = '\0'; }
			else if (c == '\?') { charLit[0] = '\\'; charLit[1] = '\?'; charLit[2] = '\0'; }
			else {	charLit[0] =  c; charLit[1] = '\0'; }
			printf("\'%s\'", charLit);
			free(charLit);
			break;
		case EXPR_BOOLEAN_LITERAL:
			printf(e->literal_value ? "true" : "false");
			break;
		case EXPR_GROUPING:
			printf("(");
			expr_print(e->left);
			printf(")");
			break;
		case EXPR_ARRAY_INIT:
			printf("{");
			expr_print(e->left);
			printf("}");
			break;
		case EXPR_SUBSCRIPT:
			expr_print(e->left);
			printf("[");
			expr_print(e->right);
			printf("]");
			break;
		case EXPR_FUNCTION_CALL:
			printf("%s(", e->name);
			expr_print(e->left);
			printf(")");
			break;
		case EXPR_INCREMENT:
			expr_print(e->left);
			printf("++");
			break;
		case EXPR_DECREMENT:
			expr_print(e->left);
			printf("--");
			break;
		case EXPR_NEGATION:
			printf("-");
			expr_print(e->left);
			break;
		case EXPR_NOT:
			printf("!");
			expr_print(e->left);
			break;
		case EXPR_EXPONENT:
			expr_print(e->left);
			printf("^");
			expr_print(e->right);
			break;
		case EXPR_MULT:
			expr_print(e->left);
			printf("*");
			expr_print(e->right);
			break;
		case EXPR_DIV:
			expr_print(e->left);
			printf("/");
			expr_print(e->right);
			break;
		case EXPR_MOD:
			expr_print(e->left);
			printf("%%");
			expr_print(e->right);
			break;
		case EXPR_ADD:
			expr_print(e->left);
			printf("+");
			expr_print(e->right);
			break;
		case EXPR_SUB:
			expr_print(e->left);
			printf("-");
			expr_print(e->right);
			break;
		case EXPR_LT:
			expr_print(e->left);
			printf("<");
			expr_print(e->right);
			break;
		case EXPR_LE:
			expr_print(e->left);
			printf("<=");
			expr_print(e->right);
			break;
		case EXPR_GT:
			expr_print(e->left);
			printf(">");
			expr_print(e->right);
			break;
		case EXPR_GE:
			expr_print(e->left);
			printf(">=");
			expr_print(e->right);
			break;
		case EXPR_EQ:
			expr_print(e->left);
			printf("==");
			expr_print(e->right);
			break;
		case EXPR_NE:
			expr_print(e->left);
			printf("!=");
			expr_print(e->right);
			break;
		case EXPR_AND:
			expr_print(e->left);
			printf("&&");
			expr_print(e->right);
			break;
		case EXPR_OR:
			expr_print(e->left);
			printf("||");
			expr_print(e->right);
			break;
		case EXPR_ASSIGN:
			expr_print(e->left);
			printf("=");
			expr_print(e->right);
			break;
	}
	if (e->next) {
		printf(",");
		expr_print(e->next);
	}
}


/* function:	expr_resolve
 * purpose:	recursively traverse the expression tree to resolve any names in
 * 		it
 */
void expr_resolve(struct expr *e, struct hash_table *h, int shouldPrint) {
	// null check
	if (!e) return;

	//resolve each side of the tree
	expr_resolve(e->left, h, shouldPrint);
	expr_resolve(e->right, h, shouldPrint);

	// if it is a name, then have to do name resolution
	if (e->kind == EXPR_NAME || e->kind == EXPR_FUNCTION_CALL) {
		struct symbol *s = scope_lookup(h, e->name);
		if (s) {
			e->symbol = s;
			if (shouldPrint) {
				printf("%s resolves to ", e->name);
				if (e->symbol->kind == SYMBOL_LOCAL) printf("local %d\n", e->symbol->which);
				else if (e->symbol->kind == SYMBOL_PARAM) printf("param %d\n", e->symbol->which);
				else printf("global %s\n", e->symbol->name);
			}
		} else {
			fprintf(stderr, "resolve error: %s not declared before use\n", e->name);
			++error_count;	
		} 
	}
	expr_resolve(e->next, h, shouldPrint);
}

/* function:	expr_delete
 * purpose:	recursively delete the expression tree
 */
void expr_delete( struct expr *e ) {
	if (!e) return;
	expr_delete(e->left);
	expr_delete(e->right);
	expr_delete(e->next);
	if (e->name) free(e->name);
	if (e->string_literal) free(e->string_literal);
	free(e);
}

/* function:	expr_typecheck
 * purpose:	recursively determine the type of the expression tree, and 
 * 		print any type errors that are found within the tree
 * 		returns the type of the expression tree <e>
 * 		NOTE: type freeing convention -- create a new one at each 
 * 		return, then free it before returning the next level up
 */
struct type *expr_typecheck( struct expr * e ) {
	if (!e) {
		return type_create(TYPE_VOID, 0, 0, 0);
	}

	struct type *a, *b;
	struct expr *e_list;

	switch (e->kind) {
		case EXPR_NAME:
			// make copy so the type is not later deleted
			return type_copy(e->symbol->type);
		case EXPR_INTEGER_LITERAL:
			return type_create(TYPE_INTEGER, 0, 0, 0);
		case EXPR_STRING_LITERAL:
			return type_create(TYPE_STRING, 0, 0, 0);
		case EXPR_CHARACTER_LITERAL:
			return type_create(TYPE_CHARACTER, 0, 0, 0);
		case EXPR_BOOLEAN_LITERAL:
			return type_create(TYPE_BOOLEAN, 0, 0, 0);
		case EXPR_GROUPING:
			return expr_typecheck(e->left);
		case EXPR_ARRAY_INIT:
			// return a new array type of that size
			// array of what though?? could be array of array
			// recursively find the subtype
			a = type_create(TYPE_ARRAY, 0, 0, 0);
			e_list = e->left;
			// do the first one outside of the while loop to set the subtype
			a->subtype = expr_typecheck(e_list);
			a->expr = expr_create_integer_literal(1);
			e_list = e_list->next;
			while (e_list) {
				if (!type_compare(a->subtype, expr_typecheck(e_list))) {
					printf("type error: types of items in array initializer (");
					expr_print(e);
					printf(") are incompatible\n");
					++error_count;
					break;
					// only need to show one error for this
				}
				// increment the number of elements in array
				a->expr->literal_value++;
				e_list = e_list->next;
			}
			return a;
		case EXPR_SUBSCRIPT:
			// e->left = name (array subscripting has to be done on an identifier - 
			//  this is checked in the parser) or another EXPR_SUBSCRIPT
			// e->right = expression within a bracket

			// have to (1) type check the expression within the brackets - it must
			//  evaluate to an integer, and (2) recurse on the left subtree to 
			//  determine the type of the result
			a = expr_typecheck(e->right);
			if (a->kind != TYPE_INTEGER) {
				printf("type error: array subscript expression cannot be ");
				type_print(a);
				printf(" (");
				expr_print(e->right);
				printf(")\n");
				++error_count;
			}
		
			b = expr_typecheck(e->left);
			if (!b->kind == TYPE_ARRAY) {
				printf("type error: trying to subscript ");
				type_print(b);
				printf(" (");
				expr_print(e->left);
				printf(")\n");
				++error_count;
				// from here, type checking is not going to be pretty the rest of
				//  the way up the expression tree
				// returning an int since there is not much that can be done
				return type_create(TYPE_INTEGER, 0, 0, 0);				
			}	
			type_delete(a);
			// returning the subtype of b because this is what the subscript operator
			//  causes it to evaluate to
			a = b->subtype;
			free(b->params);
			free(b);
			return a;
		case EXPR_FUNCTION_CALL:
			// e->left = arg list (could be null, could have non-null next member)
			// e->symbol->type is the type of the function
			
			// check the parameters against the prototype
			if (!param_list_typecheck(e->left, e->symbol->type->params)) {
				// there is an error in the function call
				printf("type error: function call (");
				expr_print(e);
				printf(") does not match the definition\n");
				++error_count;
			}

			// return the return type of that function
			// copy the type so it can't be deleted the next level up
			return type_copy(e->symbol->type->subtype);
		case EXPR_INCREMENT:
			a = expr_typecheck(e->left);
			if (a->kind != TYPE_INTEGER) {
				printf("type error: cannot increment ");
				type_print(a);
				printf(" (");
				expr_print(e->left);
				printf(")\n");
				++error_count;
			}
			type_delete(a);
			return type_create(TYPE_INTEGER, 0, 0, 0);
		case EXPR_DECREMENT:
			a = expr_typecheck(e->left);
			if (a->kind != TYPE_INTEGER) {
				printf("type error: cannot decrement ");
				type_print(a);
				printf(" (");
				expr_print(e->left);
				printf(")\n");
				++error_count;
			}
			type_delete(a);
			return type_create(TYPE_INTEGER, 0, 0, 0);
		case EXPR_NEGATION:
			a = expr_typecheck(e->left);
			if (a->kind != TYPE_INTEGER) {
				printf("type error: cannot negate ");
				type_print(a);
				printf(" (");
				expr_print(e->left);
				printf(")\n");
				++error_count;
			}
			type_delete(a);
			return type_create(TYPE_INTEGER, 0, 0, 0);
		case EXPR_NOT:
			a = expr_typecheck(e->left);
			if (a->kind != TYPE_BOOLEAN) {
				printf("type error: cannot NOT ");
				type_print(a);
				printf(" (");
				expr_print(e->left);
				printf(")\n");
				++error_count;
			}
			type_delete(a);
			return type_create(TYPE_BOOLEAN, 0, 0, 0);
		case EXPR_EXPONENT:
			a = expr_typecheck(e->left);
			b = expr_typecheck(e->right);
			if (a->kind != TYPE_INTEGER || b->kind != TYPE_INTEGER) {
				printf("type error: cannot raise ");
				type_print(a);
				printf(" (");
				expr_print(e->left);
				printf(") to power of ");
				type_print(b);
				printf(" (");
				expr_print(e->right);
				printf(")\n");
				++error_count;	
			}

			// conver this exponent expression into a function call
			e->kind = EXPR_FUNCTION_CALL;
			e->name = "integer_power";
			// add e->right to the arguments list
			e->left->next = e->right;
			e->right = 0;

			type_delete(a); 
			type_delete(b);
			// even if both sides are wrong, want to return an integer
			return type_create(TYPE_INTEGER, 0, 0, 0);
		case EXPR_MULT:
			a = expr_typecheck(e->left);
			b = expr_typecheck(e->right);
			if (a->kind != TYPE_INTEGER || b->kind != TYPE_INTEGER) {
				printf("type error: cannot multiply ");
				type_print(a);
				printf(" (");
				expr_print(e->left);
				printf(") by ");
				type_print(b);
				printf(" (");
				expr_print(e->right);
				printf(")\n");
				++error_count;
			}
			type_delete(a);
			type_delete(b);
			return type_create(TYPE_INTEGER, 0, 0, 0);
		case EXPR_DIV:
			a = expr_typecheck(e->left);
			b = expr_typecheck(e->right);
			if (a->kind != TYPE_INTEGER || b->kind != TYPE_INTEGER) {
				printf("type error: cannot divide ");
				type_print(a);
				printf(" (");
				expr_print(e->left);
				printf(") by ");
				type_print(b);
				printf(" (");
				expr_print(e->right);
				printf(")\n");
				++error_count;
			}
			type_delete(a);
			type_delete(b);
			return type_create(TYPE_INTEGER, 0, 0, 0);
		case EXPR_MOD:
			a = expr_typecheck(e->left);
			b = expr_typecheck(e->right);
			if (a->kind != TYPE_INTEGER || b->kind != TYPE_INTEGER) {
				printf("type error: cannot take mod of ");
				type_print(a);
				printf(" (");
				expr_print(e->left);
				printf(") by ");
				type_print(b);
				printf(" (");
				expr_print(e->right);
				printf(")\n");
				++error_count;
			}
			type_delete(a);
			type_delete(b);
			return type_create(TYPE_INTEGER, 0, 0, 0);
		case EXPR_ADD:
			a = expr_typecheck(e->left);
			b = expr_typecheck(e->right);
			if (a->kind != TYPE_INTEGER || b->kind != TYPE_INTEGER) {
				printf("type error: cannot add ");
				type_print(a);
				printf(" (");
				expr_print(e->left);
				printf(") and ");
				type_print(b);
				printf(" (");
				expr_print(e->right);
				printf(")\n");
				++error_count;
			}
			type_delete(a);
			type_delete(b);
			return type_create(TYPE_INTEGER, 0, 0, 0);
		case EXPR_SUB:
			a = expr_typecheck(e->left);
			b = expr_typecheck(e->right);
			if (a->kind != TYPE_INTEGER || b->kind != TYPE_INTEGER) {
				printf("type error: cannot subtract ");
				type_print(a);
				printf(" (");
				expr_print(e->left);
				printf(") and ");
				type_print(b);
				printf(" (");
				expr_print(e->right);
				printf(")\n");
				++error_count;
			}
			type_delete(a);
			type_delete(b);
			return type_create(TYPE_INTEGER, 0, 0, 0);
		case EXPR_LT:
		case EXPR_LE:
		case EXPR_GT:
		case EXPR_GE:
			a = expr_typecheck(e->left);
			b = expr_typecheck(e->right);
			if (a->kind != TYPE_INTEGER || b->kind != TYPE_INTEGER) {
				printf("type error: cannot compare ");
				type_print(a);
				printf(" (");
				expr_print(e->left);
				printf(") with ");
				type_print(b);
				printf(" (");
				expr_print(e->right);
				printf(")\n");
				++error_count;
			}
			type_delete(a);
			type_delete(b);
			return type_create(TYPE_BOOLEAN, 0, 0, 0);
		case EXPR_EQ:
		case EXPR_NE:
			// first evaluate subtrees
			a = expr_typecheck(e->left);
			b = expr_typecheck(e->right);

			// then check if either of them evaluates to an array or funcion
			if (a->kind == TYPE_ARRAY || a->kind == TYPE_FUNCTION || a->kind == TYPE_VOID || 
			  b->kind == TYPE_ARRAY || b->kind == TYPE_FUNCTION || b->kind == TYPE_VOID ||
			  !type_compare(a, b)) {
				printf("type error: cannot check for equality of ");
				type_print(a);
				printf(" (");
				expr_print(e->left);
				printf(") and ");
				type_print(b);
				printf(" (");
				expr_print(e->right);
				printf(")\n");
				++error_count;
			} else if (a->kind == TYPE_STRING) {
				// convert it into a function call of strcmp
				e->kind = EXPR_FUNCTION_CALL;
				e->name = "strcmp";
				struct expr *args = e->left;
				args->next = e->right;
				e->left = args;
			}
			type_delete(a);
			type_delete(b);	
			return type_create(TYPE_BOOLEAN, 0, 0, 0);
		case EXPR_AND:
			a = expr_typecheck(e->left);	
			b = expr_typecheck(e->right);
			if (a->kind != TYPE_BOOLEAN || b->kind != TYPE_BOOLEAN) {
				printf("type error: cannot AND ");
				type_print(a);
				printf(" (");
				expr_print(e->left);
				printf(") with ");
				type_print(b);
				printf(" (");
				expr_print(e->right);
				printf(")\n");
				++error_count;
			}
			type_delete(a);
			type_delete(b);
			return type_create(TYPE_BOOLEAN, 0, 0, 0);
		case EXPR_OR:
			a = expr_typecheck(e->left);	
			b = expr_typecheck(e->right);
			if (a->kind != TYPE_BOOLEAN || b->kind != TYPE_BOOLEAN) {
				printf("type error: cannot OR ");
				type_print(a);
				printf(" (");
				expr_print(e->left);
				printf(") with ");
				type_print(b);
				printf(" (");
				expr_print(e->right);
				printf(")\n");
				++error_count;
			}
			type_delete(a);
			type_delete(b);
			return type_create(TYPE_BOOLEAN, 0, 0, 0);
		case EXPR_ASSIGN:
			a = expr_typecheck(e->left);
			b = expr_typecheck(e->right);
			if (a->kind == TYPE_FUNCTION || a->kind == TYPE_VOID ||
			  b->kind == TYPE_FUNCTION || b->kind == TYPE_VOID ||
			  !type_compare(a, b)) {
				printf("type error: cannot assign ");
				type_print(b);
				printf(" (");
				expr_print(e->right);
				printf(") to ");
				type_print(a);
				printf(" (");
				expr_print(e->left);
				printf(")\n");
				++error_count;
			}
			type_delete(b);
			return a;	// don't delete a, but will delete further up the tree	
	}
}

/* function:	expr_isconst
 * purpose:	returns 1 if the expression is a literal value or an array 
 * 		intializer of literal values, used to determine if an expression
 * 		is valid at a global declaraion
 */
int expr_isconst( struct expr *e ) {
	// if both children are null, then it is a literal constant
	if (!e->left && !e->right) return 1;
	
	// if one the of the children is not null, and it is not an array
	//  initializer, then it is not a constant
	if (e->kind != EXPR_ARRAY_INIT) return 0;

	struct expr *elist = e->left;
	while (elist) {
		if (!expr_isconst(elist)) return 0;
		elist = elist->next;
	}
	return 1;


}

/* function:	expr_codegen
 * purpose:	recursively traverses expression tree <e> to generate
 * 		the code for it
 */
void expr_codegen (struct expr *e, FILE *f) {
	if (!e) return;

	char *s;
	int extra_reg;
	struct expr *arg;
	int argNum;
	char *jumpOpt;
	int i, j;
	char c;

	switch (e->kind) {
		case EXPR_NAME:
			e->reg = register_alloc();
			s = symbol_code(e->symbol);
			fprintf(f, "MOVQ %s, %s\n", s, register_name(e->reg));
			free(s);
			break;
		case EXPR_INTEGER_LITERAL:
		case EXPR_CHARACTER_LITERAL:
		case EXPR_BOOLEAN_LITERAL:
			e->reg = register_alloc();
			fprintf(f, "MOVQ $%d, %s\n", e->literal_value, register_name(e->reg));
			break;
		case EXPR_STRING_LITERAL:
			e->reg = register_alloc();
			// switch to data section to add the string literal as a global
			fprintf(f, ".data\n");
			fprintf(f, "STR%d:\n", string_literal_count);

			s = malloc(sizeof(char) * strlen(e->string_literal) * 2 + 1);
			for (i = 0, j = 0; i < strlen(e->string_literal); ++i, ++j) {
				c = e->string_literal[i];
				if (c == '\a') {
					s[j] = '\\';
					++j;
					s[j] = 'a';
				} else if (c == '\b') { 
					s[j] = '\\';
					++j;
					s[j] = 'b';
				} else if (c == '\f') {
					s[j] = '\\';
					++j;
					s[j] = 'f';
				} else if (c == '\n') {
					s[j] = '\\';
					++j;	
					s[j] = 'n';
				} else if (c == '\r') {
					s[j] = '\\';
					++j;
					s[j] = 'r';
				} else if (c == '\t') {
					s[j] = '\\';
					++j;
					s[j] = 't';
				} else if (c == '\v') {
					s[j] = '\\';
					++j;
					s[j] = 'v';
				} else if (c == '\"') {
					s[j] = '\\';
					++j;
					s[j] = '\"';
				} else if (c == '\\') {
					s[j] = '\\';
					++j;
					s[j] = '\\';
				} else if (c == '\'') {
					s[j] = '\\';
					++j;
					s[j] = '\'';
				} else if (c == '\?') {
					s[j] = '\\';
					++j;
					s[j] = '\?'; 
				} else {
					s[j] =  e->string_literal[i];
				}
			}
			s[j] = '\0';
			fprintf(f, ".string \"%s\"\n", s);
			free(s);

			// switch back to code section
			fprintf(f, ".text\n");
			fprintf(f, "LEA STR%d, %s\n", string_literal_count, register_name(e->reg));
			++string_literal_count;
			break;
		case EXPR_GROUPING:
			// generate the left subtree
			expr_codegen(e->left, f);
			// then pass it up the tree -- nothing to generate for a grouping
			e->reg = e->left->reg;
			break;
		case EXPR_INCREMENT:	
		case EXPR_DECREMENT:
			e->reg = register_alloc();
			expr_codegen(e->left, f);
			fprintf(f, "MOVQ %s, %s\n", register_name(e->left->reg), register_name(e->reg));
			if (e->kind == EXPR_INCREMENT) 
				fprintf(f, "ADDQ $1, %s\n", register_name(e->left->reg));
			else 
				fprintf(f, "SUBQ $1, %s\n", register_name(e->left->reg));
			s = symbol_code(e->left->symbol);
			fprintf(f, "MOVQ %s, %s\n", register_name(e->left->reg), s);
			free(s);
			register_free(e->left->reg);
			break;
		case EXPR_NEGATION:
			expr_codegen(e->left, f);
			extra_reg = register_alloc();	
			fprintf(f, "MOV $0, %s\n", register_name(extra_reg));
			fprintf(f, "SUBQ %s, %s\n", register_name(e->left->reg), register_name(extra_reg));
			register_free(e->left->reg);
			e->reg = extra_reg;
			break;
		case EXPR_ADD:
		case EXPR_SUB:
			expr_codegen(e->left, f);
			expr_codegen(e->right, f);
			if (e->kind == EXPR_ADD) 
			{
				fprintf(f, "ADDQ %s, %s\n", register_name(e->right->reg), register_name(e->left->reg));
			} else {
				fprintf(f, "SUBQ %s, %s\n", register_name(e->right->reg), register_name(e->left->reg));
			}
			e->reg = e->left->reg;
			register_free(e->right->reg);
			break;
		case EXPR_MULT:
			expr_codegen(e->left, f);
			expr_codegen(e->right, f);
			fprintf(f, "MOV %s, %%rax\n", register_name(e->left->reg));
			fprintf(f, "IMULQ %s\n", register_name(e->right->reg));
			fprintf(f, "MOV %%rax, %s\n", register_name(e->left->reg));
			e->reg = e->left->reg;
			register_free(e->right->reg);
			break;
		case EXPR_DIV:
		case EXPR_MOD:
			expr_codegen(e->left, f);
			expr_codegen(e->right, f);
			fprintf(f, "MOV %s, %%rax\n", register_name(e->left->reg));
			// sign extend rax into rdx, NOTE: don't have to save 
			//  rdx because it will be on the stack if it is needed
			fprintf(f, "CQO\n");
			// result of division goes in rax, result of mod goes inrdx
			fprintf(f, "IDIVQ %s\n", register_name(e->right->reg));
			if (e->kind == EXPR_DIV) {
				fprintf(f, "MOV %%rax, %s\n", register_name(e->left->reg));
			} else {
				fprintf(f, "MOV %%rdx, %s\n", register_name(e->left->reg));
			}
			e->reg = e->left->reg;
			register_free(e->right->reg);
			break;
		case EXPR_NOT:
			expr_codegen(e->left, f);
			fprintf(f, "NOT %s\n", register_name(e->left->reg));
			e->reg = e->left->reg;
			break;
		case EXPR_LT:
		case EXPR_LE:
		case EXPR_GT:
		case EXPR_GE:
		case EXPR_EQ:
		case EXPR_NE:
			expr_codegen(e->left, f);
			expr_codegen(e->right, f);
			fprintf(f, "CMP %s, %s\n", register_name(e->right->reg), register_name(e->left->reg));
			switch(e->kind) {
				case EXPR_LT: jumpOpt = "JL"; break;
				case EXPR_LE: jumpOpt = "JLE"; break;
				case EXPR_GT: jumpOpt = "JG"; break;
				case EXPR_GE: jumpOpt = "JGE"; break;
				case EXPR_EQ: jumpOpt = "JE"; break;
				case EXPR_NE: jumpOpt = "JNE"; break;
			}
			fprintf(f, "%s L%d\n", jumpOpt, jump_label_count);
			++jump_label_count;	//note need this minus one to print later
			e->reg = e->left->reg;
			register_free(e->right->reg);
			// if don't jump, put false in result
			fprintf(f, "MOVQ $0, %s\n", register_name(e->reg));
			fprintf(f, "JMP L%d\n", jump_label_count);
			// if jumped, put true in result
			fprintf(f, "L%d:\n", jump_label_count - 1);
			fprintf(f, "MOVQ $1, %s\n" , register_name(e->reg));
			fprintf(f, "L%d:\n", jump_label_count);
			++jump_label_count;
			break;
		case EXPR_AND:
		case EXPR_OR:
			expr_codegen(e->left, f);
			expr_codegen(e->right, f);
			if (e->kind == EXPR_AND) {
				fprintf(f, "ANDQ %s, %s\n", register_name(e->right->reg), register_name(e->left->reg));
			} else {
				fprintf(f, "ORQ %s, %s\n", register_name(e->right->reg), register_name(e->left->reg));
			}
			e->reg = e->left->reg;
			register_free(e->right->reg);
			break;
		case EXPR_ASSIGN:
			expr_codegen(e->right, f);
			s = symbol_code(e->left->symbol);
			fprintf(f, "MOVQ %s, %s\n", register_name(e->right->reg), s);	
			free(s);
			e->reg = e->right->reg;
			break;
		case EXPR_FUNCTION_CALL:
			// first need to codegen any arguments -- args in L subtree
			// also, put the results of these in the argument registers
			arg = e->left;
			argNum = 1;
			while (arg) {
				expr_codegen(arg, f);
				switch (argNum) {
					case 1: fprintf(f, "MOV %s, %%rdi\n", register_name(arg->reg)); break;
					case 2: fprintf(f, "MOV %s, %%rsi\n", register_name(arg->reg)); break;
					case 3: fprintf(f, "MOV %s, %%rdx\n", register_name(arg->reg)); break;
					case 4: fprintf(f, "MOV %s, %%rcx\n", register_name(arg->reg)); break;
					case 5: fprintf(f, "MOV %s, %%r8\n", register_name(arg->reg)); break;
					case 6: fprintf(f, "MOV %s, %%r9\n", register_name(arg->reg)); break;
					default:
						// should not get more than 6 args, if so then bug in earlier part of code
						printf("bug in code: should not have more than 6 args (%s)\n", e->name); 
						break;
				}
				register_free(arg->reg);			
				arg = arg->next;
				++argNum;
			}

			// save caller saved regs
			fprintf(f, "PUSHQ %%r10\n");
			fprintf(f, "PUSHQ %%r11\n");

			// make the function call
			fprintf(f, "CALL %s\n", e->name);			

			// restore r10 and r11
			fprintf(f, "POPQ %%r11\n");
			fprintf(f, "POPQ %%r10\n");
			e->reg = register_alloc();
			fprintf(f, "MOV %%rax, %s\n", register_name(e->reg));
			break;

		case EXPR_EXPONENT:
			// should have been converted to a function call 
			printf("bug in code: should not have an exponent expression in code gen\n");
			break;
		case EXPR_ARRAY_INIT:
		case EXPR_SUBSCRIPT:
			// not supported in code generation
			break;
	}

}
