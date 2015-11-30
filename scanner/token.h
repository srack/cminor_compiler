#ifndef TOKEN_H
#define TOKEN_H

enum token {
	ARRAY = 1,	// if starts at 0, can't distinguish from EOF
	BOOLEAN,
	CHAR,
	ELSE,
	FALSE,
	FOR,
	FUNCTION, 
	IF,
	INTEGER,
	PRINT,
	RETURN,
	STRING,
	TRUE,
	VOID,
	WHILE,
	LPAREN,
	RPAREN,
	LBRACKET,
	RBRACKET,
	LBRACE,
	RBRACE,
	COMMA,
	SEMICOLON,
	COLON,
	INCREMENT,
	DECREMENT,
	PLUS,
	MINUS,
	EXPONENT,
	MULT,
	DIVIDE,
	MOD,
	NOT,
	LT,
	LE,
	GT,
	GE,
	EQ,
	NEQ,
	AND,
	OR,
	ASSIGN,
	IDENTIFIER,
	INTEGER_LITERAL,
	CHARACTER_LITERAL,
	STRING_LITERAL,
	TOKEN_ERROR	
};
typedef enum token token_t;

int printToken(token_t t, char *ttext);
char *getEnumName(token_t t);
#endif
