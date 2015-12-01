/* Sam Rack
 * Compilers
 * main.c
 * Driver of c minor compiler. This main program can be run to either print, name resolve, typecheck, 
 * 	or perform code generation on the input c minor file.
 */

#include <stdio.h>
#include <string.h>

#include "lex.yy.h"
#include "y.tab.h"
#include "decl.h"

/// declarations of function and var generated by bison ///
extern int yyparse();
extern struct decl *program;

/// global to keep track of total number of errors found ///
int error_count = 0;

/// function prototypes for each of the program's options ///
int parse(char *filename, int shouldPrint);
int nameResolve(char *filename, int shouldPrint);
int typeCheck(char *filename);
int codeGen(char *inFile, char *outFile);

/// start main ///
int main(int argc, char **argv) {
	// check that the program has been correctly invoked
	if (argc == 3) {
		if ((strcmp(argv[1], "-print") != 0 && strcmp(argv[1], "-resolve") != 0 && strcmp(argv[1], "-typecheck") != 0)) {
			fprintf(stderr, "Usage: %s -{print|resolve|typecheck} <srcfile>\n", argv[0]);
			return 1;
		}

		if (strcmp(argv[1], "-print") == 0) {
			return parse(argv[2], 1);
		}

		if (strcmp(argv[1], "-resolve") == 0) {
			return nameResolve(argv[2], 1);
		} 

		if (strcmp(argv[1], "-typecheck") == 0) {
			return typeCheck(argv[2]);
		}
	}
	else {
		// check that the code generator has been correctly invoked
		if (argc != 4 || strcmp(argv[1], "-codegen") != 0) {
			printf("Usage: %s -codegen <src.cminor> <src.s>\n", argv[0]);
			return 1;
		}

		return codeGen(argv[2], argv[3]);
	}
}

int parse(char *filename, int shouldPrint) {
	yyin = fopen(filename, "r");
	if (!yyin) {
		fprintf(stderr, "error: cannot open %s to parse\n", filename);
		exit(1);
	}
	
	if (yyparse() == 0) { 
		if (shouldPrint) decl_print(program, 0);
		return 0;
	} else {
		exit(1);
	}

	return 0;
}

int nameResolve(char *filename, int shouldPrint) {
	// perform parse to generate AST -- AST at global <program>
	parse(filename, 0);
	// note: not checking return value because it will return 0 unless exit is called

	struct hash_table *h = hash_table_create(0, 0, 0);
	/// name resolution ///
	decl_resolve(program, &h, 0, shouldPrint, 0);

	// return appropriate value
	return error_count > 0;
}

int typeCheck(char *filename) {
	// perform parsing and name resolution
	if (nameResolve(filename, 0) != 0) {
		return 1;
	}

	// now, can do type checking on the AST
	decl_typecheck(program);	

	// return the appropriate value
	return error_count > 0;
}

int codeGen(char *inFile, char *outFile) {
	if (typeCheck(inFile) != 0) {
		return 1;
	}

	// check if there are any arrays in the source file -- if so, exit with error
	if (decl_checkForArrays(program)) {
		printf("codegen error: arrays not supported\n");
		return 1;
	}

	// check if there are any function calls with more than 6 argument -- if so, exit with error
	if (decl_tooManyArgs(program)) {
		printf("codegen error: too many arguments\n");
		return 1;
	}

	// open the file for outputting the assembly	
	FILE *f = fopen(outFile, "w");
	if (!f) {
		fprintf(stderr, "error: cannot open %s to write assembly code\n", outFile);
		return 1;
	}

	// finally, actually generate the code
	decl_codegen(program, f);
	
	// close the assembly file
	fclose(f);

	// success if got here
	return 0;
}

