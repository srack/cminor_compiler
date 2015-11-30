/* Sam Rack
 * Compilers -- Scanner
 * main.c
 */

#include <stdio.h>
#include <string.h>

#include "token.h"
#include "lex.yy.h"


int main(int argc, char **argv) {
	// check that the program has been correctly invoked
	if (argc != 3 || strcmp(argv[1], "-scan") != 0) {
		fprintf(stderr, "Usage: %s -scan <srcfile>\n", argv[0]);
		return 1;
	}

	// open the chosen file for scanning and error check
	yyin = fopen(argv[2], "r");
	if (yyin == NULL) {
		fprintf(stderr, "Error: Cannot open %s\n to scan", argv[2]);
		return 1;
	}

	// scan through the file identifying the tokens
	while (1) {
		// retrieve next token using yylex
		token_t t = yylex();

		// check if reached EOF
		if (!t)	break; 	

		// check for no token found
		if (t == TOKEN_ERROR) {
			fprintf(stderr, "Scan error: %s is not a valid token\n", yytext);
			return 1;
		}
		// printToken prints the type of the token as well as any additional 
		//  pertinent information (ie. what the string or character literal is)
		printToken(t, yytext);
		
	}


	return 0;

}
