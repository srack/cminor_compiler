/* Sam Rack
 * Compilers - Parser
 * token.c
 * This file is kept in the project so cminor can still be run with -scan option
 */

#include "token.h"
#include <stdio.h>


/* Function:	printToken()
 * Returns: 	0 if success
 * 		1 if the token passed is TOKEN_ERROR
 * Purpose:	prints the provided token 't' and any other pertinent information
 */
int printToken(int t, char *ttext) {
	if (t == TOKEN_ERROR) return 1;

	printf("%s ", getEnumName(t));

	// if printing a string or character literal, print it's contents well
	if (t == CHARACTER_LITERAL || t == STRING_LITERAL) {
		printf("%s", ttext);
	}

	printf("\n");

	return 0;
}

/* Function:	getEnumName()
 * Returns:	string matching the enum value for the provided token
 */
char *getEnumName(int t) {
	switch(t) {
		case ARRAY:		return "ARRAY";
		case BOOLEAN:		return "BOOLEAN";
		case CHAR:		return "CHAR";
		case ELSE:		return "ELSE";
		case FALSE:		return "FALSE";
		case FOR:		return "FOR";
		case FUNCTION:		return "FUNCTION";
		case IF:		return "IF";
		case INTEGER:		return "INTEGER";
		case PRINT:		return "PRINT";
		case RETURN:		return "RETURN";
		case STRING:		return "STRING";
		case TRUE:		return "TRUE";
		case VOID:		return "VOID";
		case WHILE:		return "WHILE";
		case LPAREN:		return "OPEN_PAREN";
		case RPAREN:		return "CLOSE_PAREN";
		case LBRACKET:		return "OPEN_SUBSCRIPT";
		case RBRACKET:		return "CLOSE_SUBSCRIPT";
		case LBRACE:		return "OPEN_BRACKET";
		case RBRACE:		return "CLOSE_BRACKET";
		case COMMA:		return "COMMA";
		case SEMICOLON:		return "SEMICOLON";
		case COLON:		return "COLON";
		case INCREMENT:		return "INCREMENT";
		case DECREMENT:		return "DECREMENT";
		case PLUS:		return "PLUS";
		case MINUS:		return "MINUS";
		case EXPONENT:		return "EXPONENT";
		case MULT:		return "MULT";
		case DIVIDE:		return "DIVIDE";
		case MOD:		return "MOD";
		case NOT:		return "NOT";
		case LT:		return "LT";
		case LE:		return "LE";
		case GT:		return "GT";
		case GE:		return "GE";
		case EQ:		return "EQ";
		case NEQ:		return "NEQ";
		case AND:		return "AND";
		case OR:		return "OR";
		case ASSIGN:		return "ASSIGN";
		case IDENTIFIER:	return "IDENTIFIER";
		case INTEGER_LITERAL:	return "INTEGER_LITERAL";
		case CHARACTER_LITERAL: return "CHARACTER_LITERAL";
		case STRING_LITERAL:	return "STRING_LITERAL";
		default:		return "ERROR";
	}
}
