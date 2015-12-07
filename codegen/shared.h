/* Sam Rack
 * Compilers
 * shared.h
 */

#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>

void printIndent(int indent);
void preamble_codegen(FILE *f, int numArgs, int numLocals);
void postamble_codegen(FILE *f);

#endif
