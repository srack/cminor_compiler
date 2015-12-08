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
 * 		in which the declaration is found (if not global)
 */
void decl_resolve( struct decl *d, struct hash_table **h, int whichSoFar, int shouldPrint, struct symbol *funcIn) {
	// null check
	if (!d) return;

	// check for second declaration of same name
	struct symbol *sym;
	if (sym = scope_lookup_local(*h, d->name)) {
		if (!sym->funcDefined && d->code) {
			// okay, the funciton was declared already, but this is the definition
			// but need to typecheck the declaration vs the definition
			if (!type_compare(sym->type, d->type)) {
				fprintf(stderr, "resolve error: function prototype of %s does not match its definition\n", d->name);
				++error_count;
			}
			else {
				sym->funcDefined = 1;	
				d->symbol = sym;
			}
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
			sym = symbol_create(SYMBOL_GLOBAL, 0, d->type, d->name, (d->code ? 1 : 0), 0);
		} else {
			sym = symbol_create(SYMBOL_LOCAL, whichSoFar, d->type, 0, (d->code ? 1 : 0), funcIn);
			++whichSoFar;	// another local has been added
			funcIn->numLocals = whichSoFar;
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
		stmt_resolve(d->code, h, 0, shouldPrint, d->symbol);	// whichSoFar gets reset for each function
		scope_leave(h);	
	}

	// resolve the next decl in the list
	decl_resolve(d->next, h, whichSoFar, shouldPrint, funcIn);	
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

	// if it is a function declaration, do a typecheck on the code
	// pass in the return type of the declaration to be compared on
	// return statements
	if (d->code) {
		stmt_typecheck(d->code, d);
	}
	decl_typecheck(d->next);
}

int decl_checkForArrays(struct decl *d) {
	if (!d) return 0;

	if (type_checkForArrays(d->type)) return 1;

	if (d->code && stmt_checkForArrays(d->code)) return 1;

	return decl_checkForArrays(d->next);

}

int decl_tooManyArgs(struct decl *d) {
	if (!d) return 0;

	// check number of parameters with each declaration, if there are parameters
	struct param_list *p = d->type->params;

	int count = 0;
	while(p) {
		++count;
		p = p->next;
	}
	if (count > 6) return 1;

	return decl_tooManyArgs(d->next);
}

void decl_codegen( struct decl *d, FILE *f ) {
	if (!d) return;

	// if a declaration of a variable (ie. not a function
	if (!d->code) {
		if(d->symbol->type->kind == TYPE_FUNCTION) {
			// do nothing
		} else {

			// check if it is global
			if(d->symbol->kind == SYMBOL_GLOBAL) {
				// any value it has (if it has one) will be a literal
				fprintf(f, ".data\n");
				fprintf(f, "%s: ", d->symbol->name);
				if (d->symbol->type->kind == TYPE_STRING) {
					// TODO still have to escape \n etc
					fprintf(f, ".string \"%s\"\n", d->value ? d->value->string_literal : "");
				} else {
					// default init value is 0 if not specified
					fprintf(f, ".quad %d\n", d->value ? d->value->literal_value: 0);
				}
			}
			// otherwise it is local
			else {
				// space is already allocated on the stack for these in preamble of function
				if (d->value) {
					expr_codegen(d->value, f);
					char *s = symbol_code(d->symbol);
					fprintf(f, "MOV %s, %s\n", register_name(d->value->reg), s);
					free(s);
					register_free(d->value->reg);
				}
			}
		}
	}
	// if it is a function declaration
	else {
		fprintf(f, ".text\n");
		fprintf(f, ".global %s\n", d->symbol->name);
		fprintf(f, "%s:\n", d->symbol->name);
	
		// determine the number of locals and parameters used in the function
		int numParams = 0; 
		struct param_list *p = d->type->params;
		while (p) {
			++numParams;
			p = p->next;
		}
		int numLocals = d->symbol->numLocals;	
		
		// function preamble
		preamble_codegen(f, numParams, numLocals);		
	
		// generate code for the statement list in the code
		stmt_codegen(d->code, f);
	
		// function postamble	
		postamble_codegen(f);
	}

	// generate the code for the next declaration in the list
	decl_codegen(d->next, f);

}

