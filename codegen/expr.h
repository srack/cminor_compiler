/* Sam Rack
 * Compilers
 * expr.h
 */
#ifndef EXPR_H
#define EXPR_H

#include "symbol.h"
#include "scope.h"
#include <stdlib.h>
#include <stdio.h>

extern int error_count;

typedef enum {
	EXPR_NAME,
	EXPR_INTEGER_LITERAL,
	EXPR_STRING_LITERAL,
	EXPR_CHARACTER_LITERAL,
	EXPR_BOOLEAN_LITERAL,
	EXPR_GROUPING,
	EXPR_ARRAY_INIT,
	EXPR_SUBSCRIPT,
	EXPR_FUNCTION_CALL,
	EXPR_INCREMENT,
	EXPR_DECREMENT,
	EXPR_NEGATION,
	EXPR_NOT,
	EXPR_EXPONENT,
	EXPR_MULT,
	EXPR_DIV,
	EXPR_MOD,
	EXPR_ADD,
	EXPR_SUB,
	EXPR_LT,
	EXPR_LE,
	EXPR_GT,
	EXPR_GE,
	EXPR_EQ,
	EXPR_NE,
	EXPR_AND,
	EXPR_OR,
	EXPR_ASSIGN
} expr_t;

struct expr {
	/* used by all expr types */
	expr_t kind;
	struct expr *left;
	struct expr *right;

	/* used by leaf expr types */
	char *name;
	struct symbol *symbol;
	int literal_value;
	char * string_literal;

	/* used for expr list */
	struct expr *next;
};

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right );

struct expr * expr_create_name( const char *n );
struct expr * expr_create_boolean_literal( int c );
struct expr * expr_create_integer_literal( int c );
struct expr * expr_create_character_literal( int c );
struct expr * expr_create_string_literal( const char *str );
struct expr * expr_create_function_call ( const char *n, struct expr *args );

struct expr * expr_copy( struct expr *e );

void expr_print( struct expr * e );
void expr_resolve( struct expr *e, struct hash_table *h, int shouldPrint );
void expr_delete( struct expr *e );
struct type *expr_typecheck( struct expr * e );
int expr_isconst( struct expr *e );
void expr_codegen( struct expr *e, FILE *f );
#endif
