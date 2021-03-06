/* Sam Rack
 * Compilers - Parser
 * decl.h
 */
#ifndef DECL_H
#define DECL_H

#include "shared.h"
#include "type.h"
#include "stmt.h"
#include "expr.h"
#include "scope.h"
#include "hash_table.h"
#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>

extern int error_count;

struct decl {
	char *name;
	struct type *type;
	struct expr *value;
	struct stmt *code;
	struct symbol *symbol;
	struct decl *next;
};

struct decl * decl_create( char *name, struct type *t, struct expr *v, struct stmt *c, struct decl *next );
void decl_print( struct decl *d, int indent );
void decl_resolve( struct decl *d, struct hash_table **h, int whichSoFar, int shouldPrint);
void decl_typecheck( struct decl *d);
#endif


