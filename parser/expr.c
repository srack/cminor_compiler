/* Sam Rack
 * Compilers - Parser
 * expr.c
 */
#include "expr.h"
#include <string.h>

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right ) {
	struct expr *e = malloc(sizeof(*e));
	e->kind = kind;
	e->left = left;
	e->right = right;
	return e;
}

struct expr * expr_create_name( const char *n ) {
	struct expr *e = expr_create(EXPR_NAME, 0, 0);
	e->name = malloc(sizeof(strlen(n) + 1));
	strcpy(e->name, n);
	return e;
}

struct expr * expr_create_boolean_literal( int c ) {
	struct expr *e = expr_create(EXPR_BOOLEAN_LITERAL, 0, 0);
	e->literal_value = c;
	return e;
}

struct expr * expr_create_integer_literal( int c ) {
	struct expr *e = expr_create(EXPR_INTEGER_LITERAL, 0, 0);
	e->literal_value = c;
	return e;
}

struct expr * expr_create_character_literal( int c ) {
	struct expr *e = expr_create(EXPR_CHARACTER_LITERAL, 0, 0);
	e->literal_value = c;
	return e;
}

struct expr * expr_create_string_literal( const char *str ) {
	struct expr *e = expr_create(EXPR_STRING_LITERAL, 0, 0);
	e->string_literal = malloc(sizeof(strlen(str) + 1));
	strcpy(e->string_literal, str);
	return e;
}

struct expr * expr_create_function_call( const char *n, struct expr *args ) {
	struct expr *e = expr_create(EXPR_FUNCTION_CALL, args, 0);
	e->name = malloc(sizeof(strlen(n) + 1));
	strcpy(e->name, n);
	return e;
}

void expr_print( struct expr *e ) {
	if (!e) return;
	int i, j;
	char c;
	char *charLit;
	char *strLit;
	switch(e->kind) {
		case EXPR_NAME:
			printf("%s", e->name);
			break;
		case EXPR_INTEGER_LITERAL:
			printf("%d", e->literal_value);
			break;
		case EXPR_STRING_LITERAL:
			// max length of the "extended" string is double the original (where all characters are escaped
			strLit = malloc(sizeof(char) * strlen(e->string_literal) * 2 + 1);
			for (i = 0, j = 0; i < strlen(e->string_literal); ++i, ++j) {
				c = e->string_literal[i];
				if (c == '\a') {
					strLit[j] = '\\';
					++j;
					strLit[j] = 'a';
				} else if (c == '\b') { 
					strLit[j] = '\\';
					++j;
					strLit[j] = 'b';
				} else if (c == '\f') {
					strLit[j] = '\\';
					++j;
					strLit[j] = 'f';
				} else if (c == '\n') {
					strLit[j] = '\\';
					++j;	
					strLit[j] = 'n';
				} else if (c == '\r') {
					strLit[j] = '\\';
					++j;
					strLit[j] = 'r';
				} else if (c == '\t') {
					strLit[j] = '\\';
					++j;
					strLit[j] = 't';
				} else if (c == '\v') {
					strLit[j] = '\\';
					++j;
					strLit[j] = 'v';
				} else if (c == '\"') {
					strLit[j] = '\\';
					++j;
					strLit[j] = '\"';
				} else if (c == '\\') {
					strLit[j] = '\\';
					++j;
					strLit[j] = '\\';
				} else if (c == '\'') {
					strLit[j] = '\\';
					++j;
					strLit[j] = '\'';
				} else if (c == '\?') {
					strLit[j] = '\\';
					++j;
					strLit[j] = '\?'; 
				} else {
					strLit[j] =  e->string_literal[i];
				}
			}
			strLit[j] = '\0';
			printf("\"%s\"", strLit);
			free(strLit);
			break;
		case EXPR_CHARACTER_LITERAL:
			// max size of string to be printed for the character is 3 (including null term)
			charLit = malloc(sizeof(char)*3);
			c = (char)e->literal_value;			
			if (c == '\a') { charLit[0] = '\\'; charLit[1] = 'a'; charLit[2] = '\0'; }
			else if (c == '\b') { charLit[0] = '\\'; charLit[1] = 'b'; charLit[2] = '\0'; }
			else if (c == '\f') { charLit[0] = '\\'; charLit[1] = 'f'; charLit[2] = '\0'; }
			else if (c == '\n') { charLit[0] = '\\'; charLit[1] = 'n'; charLit[2] = '\0'; }
			else if (c == '\r') { charLit[0] = '\\'; charLit[1] = 'r'; charLit[2] = '\0'; }
			else if (c == '\t') { charLit[0] = '\\'; charLit[1] = 't'; charLit[2] = '\0'; }
			else if (c == '\v') { charLit[0] = '\\'; charLit[1] = 'v'; charLit[2] = '\0'; }
			else if (c == '\"') { charLit[0] = '\\'; charLit[1] = '\"'; charLit[2] = '\0'; }
			else if (c == '\\') { charLit[0] = '\\'; charLit[1] = '\\'; charLit[2] = '\0'; }
			else if (c == '\'') { charLit[0] = '\\'; charLit[1] = '\''; charLit[2] = '\0'; }
			else if (c == '\?') { charLit[0] = '\\'; charLit[1] = '\?'; charLit[2] = '\0'; }
			else {	charLit[0] =  c; charLit[1] = '\0'; }
			printf("\'%s\'", charLit);
			free(charLit);
			break;
		case EXPR_BOOLEAN_LITERAL:
			printf(e->literal_value ? "true" : "false");
			break;
		case EXPR_GROUPING:
			printf("(");
			expr_print(e->left);
			printf(")");
			break;
		case EXPR_ARRAY_INIT:
			printf("{");
			expr_print(e->left);
			printf("}");
			break;
		case EXPR_SUBSCRIPT:
			expr_print(e->left);
			printf("[");
			expr_print(e->right);
			printf("]");
			break;
		case EXPR_FUNCTION_CALL:
			printf("%s(", e->name);
			expr_print(e->left);
			printf(")");
			break;
		case EXPR_INCREMENT:
			expr_print(e->left);
			printf("++");
			break;
		case EXPR_DECREMENT:
			expr_print(e->left);
			printf("--");
			break;
		case EXPR_NEGATION:
			printf("-");
			expr_print(e->left);
			break;
		case EXPR_NOT:
			printf("!");
			expr_print(e->left);
			break;
		case EXPR_EXPONENT:
			expr_print(e->left);
			printf("^");
			expr_print(e->right);
			break;
		case EXPR_MULT:
			expr_print(e->left);
			printf("*");
			expr_print(e->right);
			break;
		case EXPR_DIV:
			expr_print(e->left);
			printf("/");
			expr_print(e->right);
			break;
		case EXPR_MOD:
			expr_print(e->left);
			printf("%");
			expr_print(e->right);
			break;
		case EXPR_ADD:
			expr_print(e->left);
			printf("+");
			expr_print(e->right);
			break;
		case EXPR_SUB:
			expr_print(e->left);
			printf("-");
			expr_print(e->right);
			break;
		case EXPR_LT:
			expr_print(e->left);
			printf("<");
			expr_print(e->right);
			break;
		case EXPR_LE:
			expr_print(e->left);
			printf("<=");
			expr_print(e->right);
			break;
		case EXPR_GT:
			expr_print(e->left);
			printf(">");
			expr_print(e->right);
			break;
		case EXPR_GE:
			expr_print(e->left);
			printf(">=");
			expr_print(e->right);
			break;
		case EXPR_EQ:
			expr_print(e->left);
			printf("==");
			expr_print(e->right);
			break;
		case EXPR_NE:
			expr_print(e->left);
			printf("!=");
			expr_print(e->right);
			break;
		case EXPR_AND:
			expr_print(e->left);
			printf("&&");
			expr_print(e->right);
			break;
		case EXPR_OR:
			expr_print(e->left);
			printf("||");
			expr_print(e->right);
			break;
		case EXPR_ASSIGN:
			expr_print(e->left);
			printf("=");
			expr_print(e->right);
			break;
	}
	if (e->next) {
		printf(",");
		expr_print(e->next);
	}
}

