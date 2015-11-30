/* Samantha Rack
 * Compilers - Parser 
 * parser.bison
 */

/*********************
 * token definitions
 ********************/
%token ARRAY
%token BOOLEAN
%token CHAR
%token ELSE
%token FALSE
%token FOR
%token FUNCTION
%token IF
%token INTEGER
%token PRINT
%token RETURN
%token STRING
%token TRUE
%token VOID
%token WHILE
%token LPAREN
%token RPAREN
%token LBRACKET
%token RBRACKET
%token LBRACE
%token RBRACE
%token COMMA
%token SEMICOLON
%token COLON
%token INCREMENT
%token DECREMENT
%token PLUS
%token MINUS
%token EXPONENT
%token MULT
%token DIVIDE
%token MOD
%token NOT
%token LT
%token LE
%token GT
%token GE
%token EQ
%token NEQ
%token AND
%token OR
%token ASSIGN
%token IDENTIFIER
%token INTEGER_LITERAL
%token CHARACTER_LITERAL
%token STRING_LITERAL
%token TOKEN_ERROR

%union {
	struct decl *decl;
	struct stmt *stmt;
	struct expr *expr;
	struct param_list *params;
	struct type *type;
};

%type <decl> program decl_list decl
%type <stmt> stmt_list stmt matched_stmt open_stmt
%type <expr> name opt_expr_list expr_list opt_expr expr primary_expr subscript_expr incr_expr negation_expr exponent_expr mult_expr add_expr comp_expr and_expr or_expr assign_expr
%type <params> param_list nonempty_param_list param
%type <type> type

%{
/***************
 *  C preamble 
 **************/
#include <stdio.h>
#include "decl.h"
#include "expr.h"
#include "param_list.h"
#include "stmt.h"
#include "symbol.h"
#include "type.h"

extern char *yytext;
extern int yylex();
extern int yyerror(char *str);

struct decl *program = 0;

%}
%%

/****************
 * CMinor grammar
 ***************/

program: decl_list
	{ program = $1; return 0; }
	;

decl_list: decl decl_list
	{ $1->next = $2; $$ = $1; }
	| /* epsilon */
	{ $$ = 0; }
	;

decl: 	name COLON type SEMICOLON
	{ $$ = decl_create($1->name, $3, 0, 0, 0); }
	| name COLON type ASSIGN expr SEMICOLON
	{ $$ = decl_create($1->name, $3, $5, 0, 0); }
	| name COLON type ASSIGN LBRACE stmt_list RBRACE
	{ $$ = decl_create($1->name, $3, 0, $6, 0); }
	;

name:	IDENTIFIER
	{ $$ = expr_create_name(yytext); }
	;

type:	INTEGER
	{ $$ = type_create(TYPE_INTEGER, 0, 0, 0); }
	| BOOLEAN
	{ $$ = type_create(TYPE_BOOLEAN, 0, 0, 0); }
	| CHAR
	{ $$ = type_create(TYPE_CHARACTER, 0, 0, 0); }
	| STRING
	{ $$ = type_create(TYPE_STRING, 0, 0, 0); }
	| ARRAY LBRACKET opt_expr RBRACKET type
	{ $$ = type_create(TYPE_ARRAY, 0, $5, $3); }
	| FUNCTION type LPAREN param_list RPAREN
	{ $$ = type_create(TYPE_FUNCTION, $4, $2, 0); }
	| VOID
	{ $$ = type_create(TYPE_VOID, 0, 0, 0); }
	;

param_list: nonempty_param_list
	{ $$ = $1; }
	| /* epsilon */
	{ $$ = 0; }
	;

nonempty_param_list: param COMMA nonempty_param_list 
	{ $1->next = $3; $$ = $1; }
	| param
	{ $$ = $1; }
	;

param: name COLON type
	{ $$ = param_list_create($1->name, $3, 0); }
	;

stmt_list: stmt stmt_list
	{ $1->next = $2; $$ = $1; }
	| /* epsilon */
	{ $$ = 0; }
	;

stmt: open_stmt
	{ $$ = $1; }
	| matched_stmt
	{ $$ = $1; }
	;

matched_stmt: IF LPAREN expr RPAREN matched_stmt ELSE matched_stmt
	{ $$ = stmt_create(STMT_IF_ELSE, 0, $3, 0, 0, $5, $7, 0); }
	| name COLON type SEMICOLON
	{ $$ = stmt_create(STMT_DECL, decl_create($1->name, $3, 0, 0, 0), 0, 0, 0, 0, 0, 0); }
	| name COLON type ASSIGN expr SEMICOLON 
	{ $$ = stmt_create(STMT_DECL, decl_create($1->name, $3, $5, 0, 0), 0, 0, 0, 0, 0, 0); }
	| expr SEMICOLON
	{ $$ = stmt_create(STMT_EXPR, 0, 0, $1, 0, 0, 0, 0); }
	| RETURN opt_expr SEMICOLON
	{ $$ = stmt_create(STMT_RETURN, 0, 0, $2, 0, 0, 0, 0); }
	| PRINT expr_list SEMICOLON
	{ $$ = stmt_create(STMT_PRINT, 0, 0, $2, 0, 0, 0, 0); }
	| FOR LPAREN opt_expr SEMICOLON opt_expr SEMICOLON opt_expr RPAREN matched_stmt
	{ $$ = stmt_create(STMT_FOR, 0, $3, $5, $7, $9, 0, 0); }
	| LBRACE stmt_list RBRACE
	{ $$ = stmt_create(STMT_BLOCK, 0, 0, 0, 0, $2, 0, 0); }
	;

open_stmt: IF LPAREN expr RPAREN stmt
	{ $$ = stmt_create(STMT_IF_ELSE, 0, $3, 0, 0, $5, 0, 0); }
	| IF LPAREN expr RPAREN matched_stmt ELSE open_stmt
	{ $$ = stmt_create(STMT_IF_ELSE, 0, $3, 0, 0, $5, $7, 0); }
	| FOR LPAREN opt_expr SEMICOLON opt_expr SEMICOLON opt_expr RPAREN open_stmt
	{ $$ = stmt_create(STMT_FOR, 0, $3, $5, $7, $9, 0, 0); }
	;

opt_expr_list: expr_list
	{ $$ = $1; }
	| /* epsilon */
	{ $$ = 0; }
	;

expr_list: expr COMMA expr_list
	{ $1->next = $3; $$ = $1; }
	| expr
	{ $$ = $1; }
	;

opt_expr: expr
	{ $$ = $1; }
	| /* epsilon */
	{ $$ = 0; }
	;

expr: assign_expr 
	{ $$ = $1; }
	;

primary_expr: name
	{ $$ = $1; }
	| INTEGER_LITERAL
	{ $$ = expr_create_integer_literal(atoi(yytext)); }
	| STRING_LITERAL
	{ $$ = expr_create_string_literal(yytext); }
	| CHARACTER_LITERAL 
	{ $$ = expr_create_character_literal((int)yytext[0]); }
	| TRUE
	{ $$ = expr_create_boolean_literal(1); }
	| FALSE
	{ $$ = expr_create_boolean_literal(0); }
	| LPAREN expr RPAREN
	{ $$ = expr_create(EXPR_GROUPING, $2, 0); }
	| LBRACE expr_list RBRACE	/* array initializer */
	{ $$ = expr_create(EXPR_ARRAY_INIT, $2, 0); }
	| name LPAREN opt_expr_list RPAREN	/* function call */
	{ $$ = expr_create_function_call($1->name, $3); }
	| subscript_expr	/* array subscript */
	{ $$ = $1; }
	;

subscript_expr: subscript_expr LBRACKET expr RBRACKET
	{ $$ = expr_create(EXPR_SUBSCRIPT, $1, $3); }
	| name LBRACKET expr RBRACKET
	{ $$ = expr_create(EXPR_SUBSCRIPT, $1, $3); }
	;

incr_expr: primary_expr INCREMENT 
	{ $$ = expr_create(EXPR_INCREMENT, $1, 0); }
	| primary_expr DECREMENT 
	{ $$ = expr_create(EXPR_DECREMENT, $1, 0); }
	| primary_expr
	{ $$ = $1; }
	;

negation_expr: MINUS incr_expr
	{ $$ = expr_create(EXPR_NEGATION, $2, 0); }
	| NOT incr_expr
	{ $$ = expr_create(EXPR_NOT, $2, 0); }
	| incr_expr
	{ $$ = $1; }
	;

exponent_expr: exponent_expr EXPONENT negation_expr
	{ $$ = expr_create(EXPR_EXPONENT, $1, $3); }
	| negation_expr
	{ $$ = $1; }
	;

mult_expr: mult_expr MULT exponent_expr
	{ $$ = expr_create(EXPR_MULT, $1, $3); }
	| mult_expr DIVIDE exponent_expr
	{ $$ = expr_create(EXPR_DIV, $1, $3); }
	| mult_expr MOD exponent_expr
	{ $$ = expr_create(EXPR_MOD, $1, $3); }
	| exponent_expr
	{ $$ = $1; }
	;

add_expr: add_expr PLUS mult_expr
	{ $$ = expr_create(EXPR_ADD, $1, $3); }
	| add_expr MINUS mult_expr
	{ $$ = expr_create(EXPR_SUB, $1, $3); }
	| mult_expr
	{ $$ = $1; }
	;

comp_expr: comp_expr LT add_expr
	{ $$ = expr_create(EXPR_LT, $1, $3); }
	| comp_expr LE add_expr
	{ $$ = expr_create(EXPR_LE, $1, $3); }
	| comp_expr GT add_expr
	{ $$ = expr_create(EXPR_GT, $1, $3); }
	| comp_expr GE add_expr
	{ $$ = expr_create(EXPR_GE, $1, $3); }
	| comp_expr EQ add_expr
	{ $$ = expr_create(EXPR_EQ, $1, $3); }
	| comp_expr NEQ add_expr
	{ $$ = expr_create(EXPR_NE, $1, $3); }
	| add_expr
	{ $$ = $1; }
	;

and_expr: and_expr AND comp_expr
	{ $$ = expr_create(EXPR_AND, $1, $3); }
	| comp_expr
	{ $$ = $1; }
	;

or_expr: or_expr OR and_expr
	{ $$ = expr_create(EXPR_OR, $1, $3); }
	| and_expr
	{ $$ = $1; }
	;

assign_expr: assign_expr ASSIGN or_expr
	{ $$ = expr_create(EXPR_ASSIGN, $1, $3); }
	| or_expr
	{ $$ = $1; }
	;


%%

/**************
 * C postamble
 *************/
int yyerror(char *str) {
	fprintf(stderr, "parse error: %s at %s\n", str, yytext);
	return 1;
}
