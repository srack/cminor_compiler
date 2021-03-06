/* Sam Rack
 * Compilers
 * stmt.c
 */

#include "stmt.h"

int jump_label_count = 0;

/* Function: stmt_create
 */
struct stmt * stmt_create( stmt_kind_t kind, struct decl *d, struct expr *init_expr, struct expr *e, struct expr *next_expr, struct stmt *body, struct stmt *else_body, struct stmt *next ) {
	struct stmt *s = malloc(sizeof(*s));
	s->kind = kind;
	s->decl = d;
	s->init_expr = init_expr;
	s->expr = e;
	s->next_expr = next_expr;
	s->body = body;
	s->else_body = else_body;
	s->next = next;
	return s;
}

/* Function:	stmt_print
 * Params:	s -- statement list to print
 * 		indent -- number of tabs by which to indent
 * 		bodyIfFor -- used to indent a single statement extra if
 * 			and body of if/else/for is not a block statement,
 * 			set to 1 when should be added for anything except
 * 			a block statement
 */
void stmt_print( struct stmt *s, int indent, int bodyIfFor ) {
	if (!s) return;

	switch (s->kind) {
		case STMT_DECL:
			printIndent(bodyIfFor);
			// the rest of the indentation happens in decl_print
			decl_print(s->decl, indent);	
			break;
		case STMT_EXPR:
			printIndent(indent + bodyIfFor);
			expr_print(s->expr);
			printf(";");
			printf("\n");
			break;
		case STMT_IF_ELSE:
			printIndent(indent + bodyIfFor);
			printf("if (");
			expr_print(s->init_expr);
			printf(")\n");
			stmt_print(s->body, indent + bodyIfFor, 1);
			if (s->else_body) {
				printIndent(indent);
				printf("else\n");
				stmt_print(s->else_body, indent + bodyIfFor, 1);
			}
			break;
		case STMT_FOR:
			printIndent(indent + bodyIfFor);
			printf("for (");
			expr_print(s->init_expr);
			printf("; ");
			expr_print(s->expr);
			printf("; ");
			expr_print(s->next_expr);
			printf(")\n");
			stmt_print(s->body, indent + bodyIfFor, 1);
			break;
		case STMT_PRINT:
			printIndent(indent + bodyIfFor);
			printf("print ");
			expr_print(s->expr);
			printf(";");
			printf("\n");
			break;
		case STMT_RETURN:
			printIndent(indent + bodyIfFor);
			printf("return");
			if (s->expr) {
				printf(" ");
				expr_print(s->expr);
			}
			printf(";");
			printf("\n");
			break;
		case STMT_BLOCK:
			printIndent(indent);
			printf("{\n");
			stmt_print(s->body, indent+1, 0);
			printIndent(indent);
			printf("}");
			printf("\n");
			break;	
	}
	stmt_print(s->next, indent, 0);
}

/* function:	stmt_resolve
 * purpose:	recursive name resolution for the statement tree <s>, <whichSoFar>
 * 		is used to fill in the which parameter for new symbol table entries, indicates how
 * 		many of each local have been seen so far in the current function
 */
void stmt_resolve(struct stmt *s, struct hash_table **h, int whichSoFar, int shouldPrint, struct symbol *funcIn) {
	// null check
	if (!s) return;

	switch (s->kind) {
		case STMT_DECL:
			decl_resolve(s->decl, h, whichSoFar, shouldPrint, funcIn);
			++whichSoFar;
			funcIn->numLocals = whichSoFar;	
			break;
		case STMT_EXPR:
			expr_resolve(s->expr, *h, shouldPrint);
			break;
		case STMT_IF_ELSE:
			expr_resolve(s->init_expr, *h, shouldPrint);
			stmt_resolve(s->body, h, whichSoFar, shouldPrint, funcIn);
			stmt_resolve(s->else_body, h, whichSoFar, shouldPrint, funcIn);
			break;
		case STMT_FOR:
			expr_resolve(s->init_expr, *h, shouldPrint);
			expr_resolve(s->expr, *h, shouldPrint);
			expr_resolve(s->next_expr, *h, shouldPrint);
			stmt_resolve(s->body, h, whichSoFar, shouldPrint, funcIn);
			break;
		case STMT_PRINT:
			// will resolve anything in that expression list
			expr_resolve(s->expr, *h, shouldPrint);
			break;
		case STMT_RETURN:
			expr_resolve(s->expr, *h, shouldPrint);
			break;
		case STMT_BLOCK:
			scope_enter(h);
			stmt_resolve(s->body, h, whichSoFar, shouldPrint, funcIn);
			scope_leave(h);
			break;
	}

	stmt_resolve(s->next, h, whichSoFar, shouldPrint, funcIn);
}

/* function:	stmt_typecheck
 * purpose:
 */
void stmt_typecheck( struct stmt * s, struct decl * d ) {
	if (!s) return;

	struct type *t;
	// for iterating through elements in the print statement
	struct expr *e;
	// for converting elements in print statement into function calls
	struct stmt *s_next;

	switch (s->kind) {
		case STMT_DECL:
			decl_typecheck(s->decl);
			break;
		case STMT_EXPR:
			expr_typecheck(s->expr);
			break;
		case STMT_IF_ELSE:
			t = expr_typecheck(s->init_expr);
			if (t->kind != TYPE_BOOLEAN) {
				printf("type error: if conditional cannot be ");
				type_print(t);
				printf(" (");
				expr_print(s->init_expr);
				printf(")\n");
				++error_count;
			}
			stmt_typecheck(s->body, d);
			stmt_typecheck(s->else_body, d);
			break;
		case STMT_FOR:
			// don't care about the type of the first or second expression
			expr_typecheck(s->init_expr); expr_typecheck(s->next_expr);
			
			// middle type has to be void (infinite loop) or evaluate to a boolean
			t = expr_typecheck(s->expr);
			if (t->kind != TYPE_BOOLEAN && t->kind != TYPE_VOID) {
				printf("type error: middle expression in a for statement cannot be ");
				type_print(t);
				printf(" (");
				expr_print(s->expr);
				printf(")\n");
				++error_count;
			}

			// then have to type check the body
			stmt_typecheck(s->body, d);
			break;
		case STMT_PRINT:
			// all expressions in a print statement can be of any type, EXCEPT void
			e = s->expr;

			s_next = s->next;		

			// note that the list will be traversed iteratively here, instead of recursively checking through expr_typecheck since
			// 	it has a return type that may be different for each of the expressions in the list
			while (e) {
				t = expr_typecheck(e);
				if (t->kind == TYPE_VOID) {
					printf("type error: cannot have a void expression (");
					expr_print(e);
					printf(") as part of a print statement\n");
					++error_count;
				}
				// now, convert each into the appropriate function call
				s->kind = STMT_EXPR;
				
				// have to create this extra node to move the original expression down
				s->expr = expr_create_function_call("", e);
				switch(t->kind) {
					case TYPE_INTEGER:
						s->expr->name = "print_integer";
						break;
					case TYPE_STRING:
						s->expr->name = "print_string";
						break;
					case TYPE_BOOLEAN:
						s->expr->name = "print_boolean";
						break;
					case TYPE_CHARACTER:
						s->expr->name = "print_character";
						break;
					default:
						// shouldn't happen
						printf("bug in code: converting print statement to function calls\n");
						break;
				}

				e = e->next;
				s->expr->left->next = 0;
				if (e) {
					s->next = stmt_create(STMT_EXPR, 0, 0, 0, 0, 0, 0, 0);
					s = s->next;
				} else {
					s->next = s_next;
					break;
				}
			}
			break;
		case STMT_RETURN:
			t = expr_typecheck(s->expr);
			if (!type_compare(t, d->type->subtype)) {
				printf("type error: cannot return ");
				type_print(t);
				printf(" (");
				expr_print(s->expr);
				printf(") from a function (%s) that returns ", d->name);
				type_print(d->type->subtype);
				printf("\n");
				++error_count;
			}
			break;
		case STMT_BLOCK:
			stmt_typecheck(s->body, d);
			break;
	}

	stmt_typecheck(s->next, d);
}

int stmt_checkForArrays(struct stmt *s) {
	if (!s) return 0;

	if (decl_checkForArrays(s->decl)) return 1;
	
	if (stmt_checkForArrays(s->body)) return 1;

	if (stmt_checkForArrays(s->else_body)) return 1;

	return stmt_checkForArrays(s->next);
}

void stmt_codegen( struct stmt *s, FILE *f) {
	if (!s) return;

	int ifLabel;
	int elseLabel;
	int forLabel;
	int endForLabel;

	char *symb_str;

	switch (s->kind) {
		case STMT_DECL:
			decl_codegen(s->decl, f);
			break;
		case STMT_EXPR:
			expr_codegen(s->expr, f);
			register_free(s->expr->reg);
			break;
		case STMT_IF_ELSE:
			expr_codegen(s->init_expr, f);
			fprintf(f, "CMP $1, %s\n", register_name(s->init_expr->reg));
			// if the if condition is true, jump  to the if body
			fprintf(f, "JE L%d\n", jump_label_count);
			ifLabel = jump_label_count;
			++jump_label_count;
			// otherwise, fall through to the else body
			stmt_codegen(s->else_body, f);
			fprintf(f, "JMP L%d\n", jump_label_count);
			elseLabel = jump_label_count;
			++jump_label_count;
			// if body now
			fprintf(f, "L%d:\n", ifLabel);
			stmt_codegen(s->body, f);
			fprintf(f, "L%d:\n", elseLabel);
			register_free(s->init_expr->reg);
			break;
		case STMT_FOR:	
			// init expression executes once
			if (s->init_expr) {
				expr_codegen(s->init_expr, f);
				// free the register
				register_free(s->init_expr->reg);
			}

			// add a label for where to start each loop iteration
			fprintf(f, "L%d:\n", jump_label_count);
			forLabel = jump_label_count;
			++jump_label_count;

			// check the loop conditional, if one exists
			if (s->expr) {
				expr_codegen(s->expr, f);
				fprintf(f, "CMP $1, %s\n", register_name(s->expr->reg));
				// if boolean is false, time to leave the loop
				fprintf(f, "JNE L%d\n", jump_label_count);
			}
			endForLabel = jump_label_count;
			++jump_label_count;
		
			// generate code for the body of the loop
			stmt_codegen(s->body, f);
			
			// do next_expr, if one exists
			if (s->next_expr) {
				expr_codegen(s->next_expr, f);
				register_free(s->next_expr->reg);
			}
			// jump back to the beginning
			fprintf(f, "JMP L%d\n", forLabel);
			// add label for end of loop
			fprintf(f, "L%d:\n", endForLabel);

			break;
		case STMT_RETURN:
			// if there is an expression, generate code for it 
			//  and put it in rax
			if (s->expr) {
				expr_codegen(s->expr, f);
				fprintf(f, "MOV %s, %%rax\n", register_name(s->expr->reg));
				register_free(s->expr->reg);
			}

			// generate postamble of function
			postamble_codegen(f);
			break;
		case STMT_BLOCK:
			stmt_codegen(s->body, f);
			break;

		case STMT_PRINT:
			// note this shouldn't happen because it will have been 
			//  converted into function call(s)
			printf("bug in code: stmt_print should not exist by codegen step\n");
			break;
	}

	stmt_codegen(s->next, f);

}

