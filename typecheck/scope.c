#include "scope.h" 

void scope_enter(struct hash_table **ht_head) {
	// create a new hash table at head and have it point to the previous head
	*ht_head = hash_table_create(0, 0, *ht_head);
}

/* function: 	scope_leave
 * purpose:	called when the ast exists a bracket, remove the current
 * 		scope level
 */
void scope_leave(struct hash_table **ht_head) {
	if (!*ht_head) {
		// shouldn't happen, but is error
		fprintf(stderr, "resolve error: leaving too many scopes\n");
		exit(1);
	}
	//hash_table_delete(ht_head);
	*ht_head = (*ht_head)->next;
}

/* function:	scope_level
 * purpose:	iterate through list of hash tables to count the number
 * 		of levels in the list
 */
int scope_level(struct hash_table *ht_head) {
	int levels = 0;
	struct hash_table *h = ht_head;
	while (h) {
		++levels;
		h = h->next;	
	}
	return levels;
}

/* function:	scope_bind
 * purpose:	add an entry to <ht_head> table for <name>, <symbol> pair
 */
void scope_bind(struct hash_table *ht_head, const char *name, struct symbol *sym) {
	//if (!ht_head) return;
	// create an entry in the hash table to map the name to the symbol object
	if (hash_table_insert(ht_head, name, (void *)sym) == 0) {
		// shouldn't happen, but is error
		fprintf(stderr, "resolve error: hash_table_insert failed\n");
		exit(1);
	}	

}

/* function:	scope_lookup
 * purpose:	if the <name> exists in the scope (including those surrounding
 * 		the current scope), return the pointer to the symbol table
 * 		entry corresponding to that name (the most local one)
 *		if not found, return null
 */
struct symbol *scope_lookup(struct hash_table *ht_head, const char *name) {
	struct hash_table *h = ht_head;
	while (h) {
		// start by looking up the name in the current scope
		struct symbol *s = (struct symbol *)hash_table_lookup(h, name);
		// as soon as a non-null result is found, return it
		// will give the most local symbol the name refers to
		if (s) return s;
		h = h->next;
	}

	return NULL;
}

/* function: 	scope_lookup_local
 * purpose:	check if the <name> exists in the current scope, if yes, return a 
 * 		pointer to that symbol, else return null
 */
struct symbol *scope_lookup_local(struct hash_table *ht_head, const char *name) {
	if (!ht_head) return 0;
	return (struct symbol *)hash_table_lookup(ht_head, name);
}
