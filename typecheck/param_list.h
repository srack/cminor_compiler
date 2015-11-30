/* Sam Rack
 * Compilers - Parser
 * param_list.h
 */
#ifndef PARAM_LIST_H
#define PARAM_LIST_H

#include "type.h"
#include <stdio.h>
#include <stdlib.h>
#include "symbol.h"
#include "hash_table.h"
#include "string.h"
struct expr;

struct param_list {
	char *name;
	struct type *type;
	struct symbol *symbol;
	struct param_list *next;
};

struct param_list * param_list_create( char *name, struct type *type, struct param_list *next );
struct param_list * param_list_copy ( struct param_list *p );
void param_list_print( struct param_list *p );
void param_list_resolve( struct param_list *p, struct hash_table *h, int whichSoFar, int shouldPrint);
int param_list_type_compare( struct param_list *a, struct param_list *b );
void param_list_delete( struct param_list *p);
int param_list_typecheck( struct expr *e_list, struct param_list *p);

#endif
