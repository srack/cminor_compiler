/* Sam Rack
 * Compilers - Parser
 * token.h
 */
#ifndef TOKEN_H
#define TOKEN_H

#include "y.tab.h"

int printToken(int t, char *ttext);
char *getEnumName(int t);
#endif
