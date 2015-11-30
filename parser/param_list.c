/* Sam Rack
 * Compilers - Parser
 * param_list.c
 */
#include "param_list.h"

struct param_list * param_list_create( char *name, struct type *type, struct param_list *next ) {
	struct param_list *p = malloc(sizeof(*p));
	p->name = name;
	p->type = type;
	p->next = next;
	return p;
}
void param_list_print( struct param_list *a ) {
	if (!a) return;
	printf("%s: ", a->name);
	type_print(a->type);
	if (a->next) {
		printf(", ");
		param_list_print(a->next);
	}
}
