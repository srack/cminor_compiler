/* Sam Rack
 * Compilers
 * register.h
 * Interface for functions that manage register allocation for code generation.
 */

#ifndef REGISTER_H
#define REGISTER_H

#include <stdio.h>
#include <stdlib.h>

const char *register_name(int r);
int register_alloc();
void register_free(int r);


#endif
