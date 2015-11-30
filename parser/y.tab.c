#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20070509

#define YYEMPTY (-1)
#define yyclearin    (yychar = YYEMPTY)
#define yyerrok      (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

extern int yyparse(void);

static int yygrowstack(void);
#define YYPREFIX "yy"
#line 57 "parser.bison"
typedef union {
	struct decl *decl;
	struct stmt *stmt;
	struct expr *expr;
	struct param_list *params;
	struct type *type;
} YYSTYPE;
#line 72 "parser.bison"
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

#line 49 "y.tab.c"
#define ARRAY 257
#define BOOLEAN 258
#define CHAR 259
#define ELSE 260
#define FALSE 261
#define FOR 262
#define FUNCTION 263
#define IF 264
#define INTEGER 265
#define PRINT 266
#define RETURN 267
#define STRING 268
#define TRUE 269
#define VOID 270
#define WHILE 271
#define LPAREN 272
#define RPAREN 273
#define LBRACKET 274
#define RBRACKET 275
#define LBRACE 276
#define RBRACE 277
#define COMMA 278
#define SEMICOLON 279
#define COLON 280
#define INCREMENT 281
#define DECREMENT 282
#define PLUS 283
#define MINUS 284
#define EXPONENT 285
#define MULT 286
#define DIVIDE 287
#define MOD 288
#define NOT 289
#define LT 290
#define LE 291
#define GT 292
#define GE 293
#define EQ 294
#define NEQ 295
#define AND 296
#define OR 297
#define ASSIGN 298
#define IDENTIFIER 299
#define INTEGER_LITERAL 300
#define CHARACTER_LITERAL 301
#define STRING_LITERAL 302
#define TOKEN_ERROR 303
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    1,    1,    2,    2,    2,    7,   26,   26,   26,
   26,   26,   26,   26,   23,   23,   24,   24,   25,    3,
    3,    4,    4,    5,    5,    5,    5,    5,    5,    5,
    5,    6,    6,    6,    8,    8,    9,    9,   10,   10,
   11,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   13,   13,   14,   14,   14,   15,   15,   15,   16,
   16,   17,   17,   17,   17,   18,   18,   18,   19,   19,
   19,   19,   19,   19,   19,   20,   20,   21,   21,   22,
   22,
};
short yylen[] = {                                         2,
    1,    2,    0,    4,    6,    7,    1,    1,    1,    1,
    1,    5,    5,    1,    1,    0,    3,    1,    3,    2,
    0,    1,    1,    7,    4,    6,    2,    3,    3,    9,
    3,    5,    7,    9,    1,    0,    3,    1,    1,    0,
    1,    1,    1,    1,    1,    1,    1,    3,    3,    4,
    1,    4,    4,    2,    2,    1,    2,    2,    1,    3,
    1,    3,    3,    3,    1,    3,    3,    1,    3,    3,
    3,    3,    3,    3,    1,    3,    1,    3,    1,    3,
    1,
};
short yydefred[] = {                                      0,
    7,    0,    1,    0,    0,    2,    0,    0,    9,   10,
    0,    8,   11,   14,    0,    0,    0,    4,    0,   47,
   46,    0,    0,    0,    0,   43,   45,   44,    0,    0,
   39,    0,    0,   59,   61,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   57,   58,
    0,    0,    0,   54,   55,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   15,    0,    0,    0,    0,    0,    0,
    0,    0,   23,   22,    0,    0,    5,   48,   49,    0,
    0,   35,    0,   12,    0,   60,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   13,    0,    0,    0,    0,    0,    0,    6,   20,
    0,    0,   27,   37,   50,   53,   52,   19,   17,    0,
    0,   29,   28,   31,    0,    0,    0,   25,    0,    0,
   32,    0,    0,    0,    0,   26,    0,   24,   33,    0,
   30,   34,
};
short yydgoto[] = {                                       2,
    3,    4,   81,   82,   83,   84,   29,   91,   47,   30,
   31,   32,   33,   34,   35,   36,   37,   38,   39,   40,
   41,   42,   73,   74,   75,   15,
};
short yysindex[] = {                                   -284,
    0,    0,    0, -284, -260,    0,  373, -239,    0,    0,
  373,    0,    0,    0, -270, -142, -248,    0, -128,    0,
    0, -142, -142, -199, -199,    0,    0,    0, -236, -232,
    0, -251, -209,    0,    0, -194, -233, -237,  376, -203,
 -200, -204, -284, -177, -181, -169, -172, -170,    0,    0,
 -142, -142,  373,    0,    0, -142, -142, -142, -142, -142,
 -142, -142, -142, -142, -142, -142, -142, -142, -142, -142,
 -142, -171, -163,    0, -167, -159, -157, -142, -142, -177,
 -161, -177,    0,    0, -214, -222,    0,    0,    0, -142,
 -152,    0, -147,    0, -146,    0, -194, -194, -194, -233,
 -233, -237, -237, -237, -237, -237, -237,  376, -203, -200,
  373,    0, -284, -142, -142, -144, -143, -145,    0,    0,
 -140,  373,    0,    0,    0,    0,    0,    0,    0, -139,
 -136,    0,    0,    0, -258, -142, -177,    0, -142, -134,
    0, -117, -130, -142, -177,    0, -123,    0,    0, -177,
    0,    0,
};
short yyrindex[] = {                                    152,
    0,    0,    0,  152,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -122,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -98,    0,
    0,  -45,  -71,    0,    0,  -18,   86,  164,  276,  309,
  342, -111, -119, -114,    0,    0,    0, -197,    0,    0,
 -118,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -108,    0,    0,    0, -110, -114,
    0, -114,    0,    0,  367, -107,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    8,   34,   60,  112,
  138,  173,  199,  208,  234,  243,  269,  302,  316,  349,
    0,    0,    0, -110,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -110,    0,    0,    0,    0,
    0, -250,    0,  -97,    0,    0,    0,    0,    0,    0,
    0,    0,
};
short yygindex[] = {                                      0,
  174,    0,    6,   45, -127, -137,    1,    0,  -49,  -72,
  -19,    0,    0,   50,  134,    9,   17,  609,  132,  133,
  147,    0,    0,   92,    0,   -5,
};
#define YYTABLESIZE 677
short yytable[] = {                                      45,
    5,   92,   46,   48,    5,   17,  117,  149,   18,  142,
   23,   23,  152,   23,    1,   23,   23,  148,   23,    7,
  138,   23,  151,   43,   86,   23,   23,   19,  116,   54,
   55,   48,   93,   23,   16,   51,   95,   52,   23,  139,
  124,  130,   53,   72,   85,   61,   62,   94,   23,   23,
   23,   23,   58,   59,   60,   90,  123,   51,   48,   52,
   86,   20,  121,  140,   56,  122,   97,   98,   99,   21,
   48,  147,   22,   49,   50,   38,   23,  100,  101,   38,
   85,   38,   85,   20,   76,  118,   77,  120,   78,   79,
   57,   21,   69,   71,   22,  131,   70,   87,   80,    1,
   26,   27,   28,   88,   89,  128,   24,   90,  111,  112,
  113,   25,  114,   72,  115,  119,  135,  121,   20,  143,
  125,    1,   26,   27,   28,  121,   21,  126,  127,   22,
  121,  134,   20,   23,  132,  133,  137,   85,  123,  136,
   21,   24,  145,   22,  144,   85,   25,   44,  146,  150,
   85,    3,   40,   16,   36,   24,    1,   26,   27,   28,
   25,   41,   21,   41,   18,   41,   41,   41,   40,   38,
    1,   26,   27,   28,   42,   40,   42,    6,   42,   42,
   42,  141,   42,   42,   42,   42,   42,   42,   42,   42,
   96,   42,   42,   42,   42,   42,   42,   42,   42,   42,
  108,   51,  109,   51,  129,   51,   51,   51,    0,   51,
   51,   51,   51,   51,   51,   51,   51,  110,   51,   51,
   51,   51,   51,   51,   51,   51,   51,   56,    0,   56,
    0,   56,   56,   56,    0,    0,    0,   56,   56,   56,
   56,   56,   56,    0,   56,   56,   56,   56,   56,   56,
   56,   56,   56,    0,   65,    0,   65,    0,   65,   65,
   65,    0,    0,    0,   65,   65,    0,   65,   65,   65,
    0,   65,   65,   65,   65,   65,   65,   65,   65,   65,
   62,    0,   62,    0,   62,   62,   62,    0,    0,    0,
   62,   62,    0,   62,   62,   62,    0,   62,   62,   62,
   62,   62,   62,   62,   62,   62,   63,    0,   63,    0,
   63,   63,   63,    0,    0,    0,   63,   63,    0,   63,
   63,   63,    0,   63,   63,   63,   63,   63,   63,   63,
   63,   63,   64,    0,   64,    0,   64,   64,   64,    0,
    0,    0,   64,   64,    0,   64,   64,   64,    0,   64,
   64,   64,   64,   64,   64,   64,   64,   64,   68,    0,
   68,    0,   68,   68,   68,    0,    0,    0,   68,   68,
    0,    0,    0,    0,    0,   68,   68,   68,   68,   68,
   68,   68,   68,   68,   66,    0,   66,    0,   66,   66,
   66,    0,    0,    0,   66,   66,    0,    0,    0,    0,
    0,   66,   66,   66,   66,   66,   66,   66,   66,   66,
   67,    0,   67,    0,   67,   67,   67,    0,    0,    0,
   67,   67,    0,    0,    0,    0,    0,   67,   67,   67,
   67,   67,   67,   67,   67,   67,   75,    0,   75,    0,
   75,   75,   75,    0,    0,   69,    0,   69,    0,   69,
   69,   69,    0,   75,   75,   75,   75,   75,   75,   75,
   75,   75,   69,   69,   69,   69,   69,   69,   69,   69,
   69,   70,    0,   70,    0,   70,   70,   70,    0,    0,
   71,    0,   71,    0,   71,   71,   71,    0,   70,   70,
   70,   70,   70,   70,   70,   70,   70,   71,   71,   71,
   71,   71,   71,   71,   71,   71,   72,    0,   72,    0,
   72,   72,   72,    0,    0,   73,    0,   73,    0,   73,
   73,   73,    0,   72,   72,   72,   72,   72,   72,   72,
   72,   72,   73,   73,   73,   73,   73,   73,   73,   73,
   73,   74,    0,   74,    0,   74,   74,   74,   77,    0,
   77,    0,   77,   77,   77,    0,    0,    0,   74,   74,
   74,   74,   74,   74,   74,   74,   74,    0,    0,    0,
    0,   77,   77,   77,   76,    0,   76,    0,   76,   76,
   76,   79,    0,   79,    0,   79,   79,   79,   78,    0,
   78,    0,   78,   78,   78,    0,    0,   76,   76,   76,
    0,    0,    0,    0,    0,   79,   79,    0,    0,    0,
    0,    0,   78,   78,   81,    0,   81,    0,   81,   81,
   81,   80,    0,   80,    0,   80,   80,   80,    0,    8,
    9,   10,    0,    0,    0,   11,    0,   12,    0,   81,
   13,    0,   14,   42,   42,   42,   80,   42,   42,   42,
   42,   42,   42,   42,   42,    0,   42,   42,   42,   42,
   42,   42,   42,   42,   42,   63,   64,   65,   66,   67,
   68,  102,  103,  104,  105,  106,  107,
};
short yycheck[] = {                                      19,
    0,   51,   22,   23,    4,   11,   79,  145,  279,  137,
  261,  262,  150,  264,  299,  266,  267,  145,  269,  280,
  279,  272,  150,  272,   44,  276,  277,  298,   78,  281,
  282,   51,   52,  284,  274,  272,   56,  274,  289,  298,
   90,  114,  275,   43,   44,  283,  284,   53,  299,  300,
  301,  302,  286,  287,  288,  278,  279,  272,   78,  274,
   80,  261,   82,  136,  274,  280,   58,   59,   60,  269,
   90,  144,  272,   24,   25,  273,  276,   61,   62,  277,
   80,  279,   82,  261,  262,   80,  264,   82,  266,  267,
  285,  269,  296,  298,  272,  115,  297,  279,  276,  299,
  300,  301,  302,  273,  277,  111,  284,  278,  280,  273,
  278,  289,  272,  113,  272,  277,  122,  137,  261,  139,
  273,  299,  300,  301,  302,  145,  269,  275,  275,  272,
  150,  277,  261,  276,  279,  279,  273,  137,  279,  279,
  269,  284,  260,  272,  279,  145,  289,  276,  279,  273,
  150,    0,  275,  273,  273,  284,  299,  300,  301,  302,
  289,  273,  277,  275,  273,  277,  278,  279,  279,  277,
  299,  300,  301,  302,  273,  273,  275,    4,  277,  278,
  279,  137,  281,  282,  283,  284,  285,  286,  287,  288,
   57,  290,  291,  292,  293,  294,  295,  296,  297,  298,
   69,  273,   70,  275,  113,  277,  278,  279,   -1,  281,
  282,  283,  284,  285,  286,  287,  288,   71,  290,  291,
  292,  293,  294,  295,  296,  297,  298,  273,   -1,  275,
   -1,  277,  278,  279,   -1,   -1,   -1,  283,  284,  285,
  286,  287,  288,   -1,  290,  291,  292,  293,  294,  295,
  296,  297,  298,   -1,  273,   -1,  275,   -1,  277,  278,
  279,   -1,   -1,   -1,  283,  284,   -1,  286,  287,  288,
   -1,  290,  291,  292,  293,  294,  295,  296,  297,  298,
  273,   -1,  275,   -1,  277,  278,  279,   -1,   -1,   -1,
  283,  284,   -1,  286,  287,  288,   -1,  290,  291,  292,
  293,  294,  295,  296,  297,  298,  273,   -1,  275,   -1,
  277,  278,  279,   -1,   -1,   -1,  283,  284,   -1,  286,
  287,  288,   -1,  290,  291,  292,  293,  294,  295,  296,
  297,  298,  273,   -1,  275,   -1,  277,  278,  279,   -1,
   -1,   -1,  283,  284,   -1,  286,  287,  288,   -1,  290,
  291,  292,  293,  294,  295,  296,  297,  298,  273,   -1,
  275,   -1,  277,  278,  279,   -1,   -1,   -1,  283,  284,
   -1,   -1,   -1,   -1,   -1,  290,  291,  292,  293,  294,
  295,  296,  297,  298,  273,   -1,  275,   -1,  277,  278,
  279,   -1,   -1,   -1,  283,  284,   -1,   -1,   -1,   -1,
   -1,  290,  291,  292,  293,  294,  295,  296,  297,  298,
  273,   -1,  275,   -1,  277,  278,  279,   -1,   -1,   -1,
  283,  284,   -1,   -1,   -1,   -1,   -1,  290,  291,  292,
  293,  294,  295,  296,  297,  298,  273,   -1,  275,   -1,
  277,  278,  279,   -1,   -1,  273,   -1,  275,   -1,  277,
  278,  279,   -1,  290,  291,  292,  293,  294,  295,  296,
  297,  298,  290,  291,  292,  293,  294,  295,  296,  297,
  298,  273,   -1,  275,   -1,  277,  278,  279,   -1,   -1,
  273,   -1,  275,   -1,  277,  278,  279,   -1,  290,  291,
  292,  293,  294,  295,  296,  297,  298,  290,  291,  292,
  293,  294,  295,  296,  297,  298,  273,   -1,  275,   -1,
  277,  278,  279,   -1,   -1,  273,   -1,  275,   -1,  277,
  278,  279,   -1,  290,  291,  292,  293,  294,  295,  296,
  297,  298,  290,  291,  292,  293,  294,  295,  296,  297,
  298,  273,   -1,  275,   -1,  277,  278,  279,  273,   -1,
  275,   -1,  277,  278,  279,   -1,   -1,   -1,  290,  291,
  292,  293,  294,  295,  296,  297,  298,   -1,   -1,   -1,
   -1,  296,  297,  298,  273,   -1,  275,   -1,  277,  278,
  279,  273,   -1,  275,   -1,  277,  278,  279,  273,   -1,
  275,   -1,  277,  278,  279,   -1,   -1,  296,  297,  298,
   -1,   -1,   -1,   -1,   -1,  297,  298,   -1,   -1,   -1,
   -1,   -1,  297,  298,  273,   -1,  275,   -1,  277,  278,
  279,  273,   -1,  275,   -1,  277,  278,  279,   -1,  257,
  258,  259,   -1,   -1,   -1,  263,   -1,  265,   -1,  298,
  268,   -1,  270,  277,  278,  279,  298,  281,  282,  283,
  284,  285,  286,  287,  288,   -1,  290,  291,  292,  293,
  294,  295,  296,  297,  298,  290,  291,  292,  293,  294,
  295,   63,   64,   65,   66,   67,   68,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 303
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"ARRAY","BOOLEAN","CHAR","ELSE",
"FALSE","FOR","FUNCTION","IF","INTEGER","PRINT","RETURN","STRING","TRUE","VOID",
"WHILE","LPAREN","RPAREN","LBRACKET","RBRACKET","LBRACE","RBRACE","COMMA",
"SEMICOLON","COLON","INCREMENT","DECREMENT","PLUS","MINUS","EXPONENT","MULT",
"DIVIDE","MOD","NOT","LT","LE","GT","GE","EQ","NEQ","AND","OR","ASSIGN",
"IDENTIFIER","INTEGER_LITERAL","CHARACTER_LITERAL","STRING_LITERAL",
"TOKEN_ERROR",
};
char *yyrule[] = {
"$accept : program",
"program : decl_list",
"decl_list : decl decl_list",
"decl_list :",
"decl : name COLON type SEMICOLON",
"decl : name COLON type ASSIGN expr SEMICOLON",
"decl : name COLON type ASSIGN LBRACE stmt_list RBRACE",
"name : IDENTIFIER",
"type : INTEGER",
"type : BOOLEAN",
"type : CHAR",
"type : STRING",
"type : ARRAY LBRACKET opt_expr RBRACKET type",
"type : FUNCTION type LPAREN param_list RPAREN",
"type : VOID",
"param_list : nonempty_param_list",
"param_list :",
"nonempty_param_list : param COMMA nonempty_param_list",
"nonempty_param_list : param",
"param : name COLON type",
"stmt_list : stmt stmt_list",
"stmt_list :",
"stmt : open_stmt",
"stmt : matched_stmt",
"matched_stmt : IF LPAREN expr RPAREN matched_stmt ELSE matched_stmt",
"matched_stmt : name COLON type SEMICOLON",
"matched_stmt : name COLON type ASSIGN expr SEMICOLON",
"matched_stmt : expr SEMICOLON",
"matched_stmt : RETURN opt_expr SEMICOLON",
"matched_stmt : PRINT expr_list SEMICOLON",
"matched_stmt : FOR LPAREN opt_expr SEMICOLON opt_expr SEMICOLON opt_expr RPAREN matched_stmt",
"matched_stmt : LBRACE stmt_list RBRACE",
"open_stmt : IF LPAREN expr RPAREN stmt",
"open_stmt : IF LPAREN expr RPAREN matched_stmt ELSE open_stmt",
"open_stmt : FOR LPAREN opt_expr SEMICOLON opt_expr SEMICOLON opt_expr RPAREN open_stmt",
"opt_expr_list : expr_list",
"opt_expr_list :",
"expr_list : expr COMMA expr_list",
"expr_list : expr",
"opt_expr : expr",
"opt_expr :",
"expr : assign_expr",
"primary_expr : name",
"primary_expr : INTEGER_LITERAL",
"primary_expr : STRING_LITERAL",
"primary_expr : CHARACTER_LITERAL",
"primary_expr : TRUE",
"primary_expr : FALSE",
"primary_expr : LPAREN expr RPAREN",
"primary_expr : LBRACE expr_list RBRACE",
"primary_expr : name LPAREN opt_expr_list RPAREN",
"primary_expr : subscript_expr",
"subscript_expr : subscript_expr LBRACKET expr RBRACKET",
"subscript_expr : name LBRACKET expr RBRACKET",
"incr_expr : primary_expr INCREMENT",
"incr_expr : primary_expr DECREMENT",
"incr_expr : primary_expr",
"negation_expr : MINUS incr_expr",
"negation_expr : NOT incr_expr",
"negation_expr : incr_expr",
"exponent_expr : exponent_expr EXPONENT negation_expr",
"exponent_expr : negation_expr",
"mult_expr : mult_expr MULT exponent_expr",
"mult_expr : mult_expr DIVIDE exponent_expr",
"mult_expr : mult_expr MOD exponent_expr",
"mult_expr : exponent_expr",
"add_expr : add_expr PLUS mult_expr",
"add_expr : add_expr MINUS mult_expr",
"add_expr : mult_expr",
"comp_expr : comp_expr LT add_expr",
"comp_expr : comp_expr LE add_expr",
"comp_expr : comp_expr GT add_expr",
"comp_expr : comp_expr GE add_expr",
"comp_expr : comp_expr EQ add_expr",
"comp_expr : comp_expr NEQ add_expr",
"comp_expr : add_expr",
"and_expr : and_expr AND comp_expr",
"and_expr : comp_expr",
"or_expr : or_expr OR and_expr",
"or_expr : and_expr",
"assign_expr : assign_expr ASSIGN or_expr",
"assign_expr : or_expr",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static int      yystacksize;
#line 314 "parser.bison"

/**************
 * C postamble
 *************/
int yyerror(char *str) {
	fprintf(stderr, "parse error: %s at %s\n", str, yytext);
	return 1;
}
#line 473 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

#ifdef lint
    goto yyerrlab;
#endif

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 97 "parser.bison"
{ program = yyvsp[0].decl; return 0; }
break;
case 2:
#line 101 "parser.bison"
{ yyvsp[-1].decl->next = yyvsp[0].decl; yyval.decl = yyvsp[-1].decl; }
break;
case 3:
#line 103 "parser.bison"
{ yyval.decl = 0; }
break;
case 4:
#line 107 "parser.bison"
{ yyval.decl = decl_create(yyvsp[-3].expr->name, yyvsp[-1].type, 0, 0, 0); }
break;
case 5:
#line 109 "parser.bison"
{ yyval.decl = decl_create(yyvsp[-5].expr->name, yyvsp[-3].type, yyvsp[-1].expr, 0, 0); }
break;
case 6:
#line 111 "parser.bison"
{ yyval.decl = decl_create(yyvsp[-6].expr->name, yyvsp[-4].type, 0, yyvsp[-1].stmt, 0); }
break;
case 7:
#line 115 "parser.bison"
{ yyval.expr = expr_create_name(yytext); }
break;
case 8:
#line 119 "parser.bison"
{ yyval.type = type_create(TYPE_INTEGER, 0, 0, 0); }
break;
case 9:
#line 121 "parser.bison"
{ yyval.type = type_create(TYPE_BOOLEAN, 0, 0, 0); }
break;
case 10:
#line 123 "parser.bison"
{ yyval.type = type_create(TYPE_CHARACTER, 0, 0, 0); }
break;
case 11:
#line 125 "parser.bison"
{ yyval.type = type_create(TYPE_STRING, 0, 0, 0); }
break;
case 12:
#line 127 "parser.bison"
{ yyval.type = type_create(TYPE_ARRAY, 0, yyvsp[0].type, yyvsp[-2].expr); }
break;
case 13:
#line 129 "parser.bison"
{ yyval.type = type_create(TYPE_FUNCTION, yyvsp[-1].params, yyvsp[-3].type, 0); }
break;
case 14:
#line 131 "parser.bison"
{ yyval.type = type_create(TYPE_VOID, 0, 0, 0); }
break;
case 15:
#line 135 "parser.bison"
{ yyval.params = yyvsp[0].params; }
break;
case 16:
#line 137 "parser.bison"
{ yyval.params = 0; }
break;
case 17:
#line 141 "parser.bison"
{ yyvsp[-2].params->next = yyvsp[0].params; yyval.params = yyvsp[-2].params; }
break;
case 18:
#line 143 "parser.bison"
{ yyval.params = yyvsp[0].params; }
break;
case 19:
#line 147 "parser.bison"
{ yyval.params = param_list_create(yyvsp[-2].expr->name, yyvsp[0].type, 0); }
break;
case 20:
#line 151 "parser.bison"
{ yyvsp[-1].stmt->next = yyvsp[0].stmt; yyval.stmt = yyvsp[-1].stmt; }
break;
case 21:
#line 153 "parser.bison"
{ yyval.stmt = 0; }
break;
case 22:
#line 157 "parser.bison"
{ yyval.stmt = yyvsp[0].stmt; }
break;
case 23:
#line 159 "parser.bison"
{ yyval.stmt = yyvsp[0].stmt; }
break;
case 24:
#line 163 "parser.bison"
{ yyval.stmt = stmt_create(STMT_IF_ELSE, 0, yyvsp[-4].expr, 0, 0, yyvsp[-2].stmt, yyvsp[0].stmt, 0); }
break;
case 25:
#line 165 "parser.bison"
{ yyval.stmt = stmt_create(STMT_DECL, decl_create(yyvsp[-3].expr->name, yyvsp[-1].type, 0, 0, 0), 0, 0, 0, 0, 0, 0); }
break;
case 26:
#line 167 "parser.bison"
{ yyval.stmt = stmt_create(STMT_DECL, decl_create(yyvsp[-5].expr->name, yyvsp[-3].type, yyvsp[-1].expr, 0, 0), 0, 0, 0, 0, 0, 0); }
break;
case 27:
#line 169 "parser.bison"
{ yyval.stmt = stmt_create(STMT_EXPR, 0, 0, yyvsp[-1].expr, 0, 0, 0, 0); }
break;
case 28:
#line 171 "parser.bison"
{ yyval.stmt = stmt_create(STMT_RETURN, 0, 0, yyvsp[-1].expr, 0, 0, 0, 0); }
break;
case 29:
#line 173 "parser.bison"
{ yyval.stmt = stmt_create(STMT_PRINT, 0, 0, yyvsp[-1].expr, 0, 0, 0, 0); }
break;
case 30:
#line 175 "parser.bison"
{ yyval.stmt = stmt_create(STMT_FOR, 0, yyvsp[-6].expr, yyvsp[-4].expr, yyvsp[-2].expr, yyvsp[0].stmt, 0, 0); }
break;
case 31:
#line 177 "parser.bison"
{ yyval.stmt = stmt_create(STMT_BLOCK, 0, 0, 0, 0, yyvsp[-1].stmt, 0, 0); }
break;
case 32:
#line 181 "parser.bison"
{ yyval.stmt = stmt_create(STMT_IF_ELSE, 0, yyvsp[-2].expr, 0, 0, yyvsp[0].stmt, 0, 0); }
break;
case 33:
#line 183 "parser.bison"
{ yyval.stmt = stmt_create(STMT_IF_ELSE, 0, yyvsp[-4].expr, 0, 0, yyvsp[-2].stmt, yyvsp[0].stmt, 0); }
break;
case 34:
#line 185 "parser.bison"
{ yyval.stmt = stmt_create(STMT_FOR, 0, yyvsp[-6].expr, yyvsp[-4].expr, yyvsp[-2].expr, yyvsp[0].stmt, 0, 0); }
break;
case 35:
#line 189 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 36:
#line 191 "parser.bison"
{ yyval.expr = 0; }
break;
case 37:
#line 195 "parser.bison"
{ yyvsp[-2].expr->next = yyvsp[0].expr; yyval.expr = yyvsp[-2].expr; }
break;
case 38:
#line 197 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 39:
#line 201 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 40:
#line 203 "parser.bison"
{ yyval.expr = 0; }
break;
case 41:
#line 207 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 42:
#line 211 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 43:
#line 213 "parser.bison"
{ yyval.expr = expr_create_integer_literal(atoi(yytext)); }
break;
case 44:
#line 215 "parser.bison"
{ yyval.expr = expr_create_string_literal(yytext); }
break;
case 45:
#line 217 "parser.bison"
{ yyval.expr = expr_create_character_literal((int)yytext[0]); }
break;
case 46:
#line 219 "parser.bison"
{ yyval.expr = expr_create_boolean_literal(1); }
break;
case 47:
#line 221 "parser.bison"
{ yyval.expr = expr_create_boolean_literal(0); }
break;
case 48:
#line 223 "parser.bison"
{ yyval.expr = expr_create(EXPR_GROUPING, yyvsp[-1].expr, 0); }
break;
case 49:
#line 225 "parser.bison"
{ yyval.expr = expr_create(EXPR_ARRAY_INIT, yyvsp[-1].expr, 0); }
break;
case 50:
#line 227 "parser.bison"
{ yyval.expr = expr_create_function_call(yyvsp[-3].expr->name, yyvsp[-1].expr); }
break;
case 51:
#line 229 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 52:
#line 233 "parser.bison"
{ yyval.expr = expr_create(EXPR_SUBSCRIPT, yyvsp[-3].expr, yyvsp[-1].expr); }
break;
case 53:
#line 235 "parser.bison"
{ yyval.expr = expr_create(EXPR_SUBSCRIPT, yyvsp[-3].expr, yyvsp[-1].expr); }
break;
case 54:
#line 239 "parser.bison"
{ yyval.expr = expr_create(EXPR_INCREMENT, yyvsp[-1].expr, 0); }
break;
case 55:
#line 241 "parser.bison"
{ yyval.expr = expr_create(EXPR_DECREMENT, yyvsp[-1].expr, 0); }
break;
case 56:
#line 243 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 57:
#line 247 "parser.bison"
{ yyval.expr = expr_create(EXPR_NEGATION, yyvsp[0].expr, 0); }
break;
case 58:
#line 249 "parser.bison"
{ yyval.expr = expr_create(EXPR_NOT, yyvsp[0].expr, 0); }
break;
case 59:
#line 251 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 60:
#line 255 "parser.bison"
{ yyval.expr = expr_create(EXPR_EXPONENT, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 61:
#line 257 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 62:
#line 261 "parser.bison"
{ yyval.expr = expr_create(EXPR_MULT, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 63:
#line 263 "parser.bison"
{ yyval.expr = expr_create(EXPR_DIV, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 64:
#line 265 "parser.bison"
{ yyval.expr = expr_create(EXPR_MOD, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 65:
#line 267 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 66:
#line 271 "parser.bison"
{ yyval.expr = expr_create(EXPR_ADD, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 67:
#line 273 "parser.bison"
{ yyval.expr = expr_create(EXPR_SUB, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 68:
#line 275 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 69:
#line 279 "parser.bison"
{ yyval.expr = expr_create(EXPR_LT, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 70:
#line 281 "parser.bison"
{ yyval.expr = expr_create(EXPR_LE, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 71:
#line 283 "parser.bison"
{ yyval.expr = expr_create(EXPR_GT, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 72:
#line 285 "parser.bison"
{ yyval.expr = expr_create(EXPR_GE, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 73:
#line 287 "parser.bison"
{ yyval.expr = expr_create(EXPR_EQ, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 74:
#line 289 "parser.bison"
{ yyval.expr = expr_create(EXPR_NE, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 75:
#line 291 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 76:
#line 295 "parser.bison"
{ yyval.expr = expr_create(EXPR_AND, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 77:
#line 297 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 78:
#line 301 "parser.bison"
{ yyval.expr = expr_create(EXPR_OR, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 79:
#line 303 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
case 80:
#line 307 "parser.bison"
{ yyval.expr = expr_create(EXPR_ASSIGN, yyvsp[-2].expr, yyvsp[0].expr); }
break;
case 81:
#line 309 "parser.bison"
{ yyval.expr = yyvsp[0].expr; }
break;
#line 978 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
