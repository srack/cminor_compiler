/* Sam Rack
 * Compilers - Parser
 * stmt.c
 */
#include "stmt.h"

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
