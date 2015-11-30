/* Sam Rack
 * Compilers
 * shared.c
 */

#include "shared.h"

void printIndent(int indent) {
	int i;
	for (i = 0; i < indent; ++i) {
		printf("\t");
	}
}
