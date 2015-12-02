/* Sam Rack
 * Compilers
 * scope.h
 * Interface for functions that manage scope during name resolution of the compilation process. 
 */

#ifndef SCOPE_H
#define SCOPE_H

#include "hash_table.h"
#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>

void scope_enter(struct hash_table **ht_head);
void scope_leave(struct hash_table **ht_head);
int scope_level(struct hash_table *ht_head);
void scope_bind(struct hash_table *ht_head, const char *name, struct symbol *sym);
struct symbol *scope_lookup(struct hash_table *ht_head, const char *name);
struct symbol *scope_lookup_local(struct hash_table *ht_head, const char *name);

#endif
