/* Sam Rack
 * Compilers
 * stmt.h
 * Interface for functions that handle statements in c minor code.
 */

#ifndef STMT_H
#define STMT_H

#include "shared.h"
#include "decl.h"
#include "scope.h"
#include <stdlib.h>

typedef enum {
	STMT_DECL,
	STMT_EXPR,
	STMT_IF_ELSE,
	STMT_FOR,
	STMT_PRINT,
	STMT_RETURN,
	STMT_BLOCK
} stmt_kind_t;

struct stmt {
	stmt_kind_t kind;
	struct decl *decl;
	struct expr *init_expr;
	struct expr *expr;
	struct expr *next_expr;
	struct stmt *body;
	struct stmt *else_body;
	struct stmt *next;
};

struct stmt * stmt_create( stmt_kind_t kind, struct decl *d, struct expr *init_expr, struct expr *e, struct expr *next_expr, struct stmt *body, struct stmt *else_body, struct stmt *next );
void stmt_print( struct stmt *s, int indent, int below_ifFor );
void stmt_resolve( struct stmt *s, struct hash_table **h, int whichSoFar, int shouldPrint );
void stmt_typecheck( struct stmt * s, struct decl * d );
void stmt_codegen( struct stmt *s, FILE *f);
int stmt_checkForArrays(struct stmt *s);
#endif
