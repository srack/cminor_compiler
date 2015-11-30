/* Sam Rack
 * Compilers - Parser
 * main.c
 */

#include <stdio.h>
#include <string.h>

#include "lex.yy.h"
#include "token.h"

extern int yyparse();
extern struct decl *program;

int scanFile(char *filename);
int parseFile(char *filename);

int main(int argc, char **argv) {
	// check that the program has been correctly invoked
	if (argc != 3 || (strcmp(argv[1], "-scan") != 0 && strcmp(argv[1], "-parse") != 0)) {
		fprintf(stderr, "Usage: %s -{scan|parse} <srcfile>\n", argv[0]);
		return 1;
	}

	if (strcmp(argv[1], "-scan") == 0) {
		return scanFile(argv[2]);
	}

	if (strcmp(argv[1], "-parse") == 0) {
		return parseFile(argv[2]);
	} 

}

/* Function: 	scanFile
 * Purpose:	Executes funcionality for scanner assignment, called when program is run with 
 * 		-scan option
 */
int scanFile(char *filename) {
	// open the chosen file for scanning and error check
	yyin = fopen(filename, "r");
	if (yyin == NULL) {
		fprintf(stderr, "Error: Cannot open %s to scan", filename);
		return 1;
	}

	// scan through the file identifying the tokens
	while (1) {
		// retrieve next token using yylex
		int t = yylex();

		// check if reached EOF
		if (!t)	break; 	

		// check for no token found
		if (t == TOKEN_ERROR) {
			fprintf(stderr, "scan error: %s is not a valid token\n", yytext);
			return 1;
		}
		// printToken prints the type of the token as well as any additional 
		//  pertinent information (ie. what the string or character literal is)
		printToken(t, yytext);
		
	}

	return 0;
}

int parseFile(char *filename) {
	yyin = fopen(filename, "r");
	if (yyin == NULL) {
		fprintf(stderr, "Error: Cannot open %s to parse", filename);
		return 1;
	}
	
	if (yyparse() == 0) { 
		decl_print(program, 0);
		return 0;
	} else {
		exit(1);
	}

	

	return 0;
}
