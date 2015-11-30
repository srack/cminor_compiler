/* Sam Rack
 * Compilers - Scanner
 * scanner.l
 */

%{
#include "token.h"
#include <string.h>
#include <limits.h>

%}

%option noyywrap

NUMBER	[0-9]
LETTER	[a-zA-Z]
LETTER_	{LETTER}|_
WHITESPACE [\n\t\r ]

%%
array	{ return ARRAY; }
boolean	{ return BOOLEAN; }
char	{ return CHAR; }
else	{ return ELSE; }
false	{ return FALSE; }
for	{ return FOR; }
function	{ return FUNCTION; }
if	{ return IF; }
integer	{ return INTEGER; }
print	{ return PRINT; }
return	{ return RETURN; }
string	{ return STRING; }
true	{ return TRUE; }
void	{ return VOID; }
while	{ return WHILE; }

{WHITESPACE}	{ }
\/\/.* 	{ }	
\/\*([^\*]|((\*)+[^\/\*]))*(\*)+\/	{ }

\(	{ return LPAREN; }
\)	{ return RPAREN; }
\[	{ return LBRACKET; }
\]	{ return RBRACKET; }
\{	{ return LBRACE; }
\}	{ return RBRACE; }
\,	{ return COMMA; }
\;	{ return SEMICOLON; }
\:	{ return COLON; }
\+\+	{ return INCREMENT; }
\-\-	{ return DECREMENT; }
\+	{ return PLUS; }
\-	{ return MINUS; }
\^	{ return EXPONENT; }
\*	{ return MULT; }
\/	{ return DIVIDE; }
\%	{ return MOD; }
\!	{ return NOT; }
\<	{ return LT; }
\<\=	{ return LE; }
\>	{ return GT; }
\>\=	{ return GE; }
\=\=	{ return EQ; }
\!\=	{ return NEQ; }
\&\&	{ return AND; }
\|\|	{ return OR; }
\=	{ return ASSIGN; }


{LETTER_}({LETTER_}|{NUMBER})*	{ return IDENTIFIER; }

{NUMBER}+	{ 
	char * maxSizeAsString = malloc(sizeof(char)*20);
	sprintf(maxSizeAsString, "%ld\0", LONG_MAX); //32 bits
	if (strlen(yytext) > strlen(maxSizeAsString)){
		return TOKEN_ERROR;
	}
	else if (atoll(yytext) > LONG_MAX || atoll(yytext) < LONG_MIN) {
		return TOKEN_ERROR;
	}
	free(maxSizeAsString);

	return INTEGER_LITERAL; 
}

\'([^\\]|\\.)\'	{ 
	
	char *tmp = malloc(sizeof(char)*(strlen(yytext)+1));
	strncpy(tmp, yytext, strlen(yytext));
	
	// if string length is 3 then it is a "normal" character
	if (strlen(yytext) == 3) {
		yytext[0] = tmp[1];
	}
	// otherwise, it is an escaped character
	else {
		switch(tmp[2]) {
			case 'a': yytext[0] = '\a'; break;
			case 'b': yytext[0] = '\b'; break;
			case 'f': yytext[0] = '\f'; break;
			case 'n': yytext[0] = '\n'; break;
			case 'r': yytext[0] = '\r'; break;
			case 't': yytext[0] = '\t'; break;
			case 'v': yytext[0] = '\v'; break;
			default: yytext[0] = tmp[2]; break;
		}
	}
	free(tmp);
	yytext[1] = '\0';

	return CHARACTER_LITERAL; 
}

\"([^\n\"]|\\\")*\" { 
	char *tmp = malloc(sizeof(char)*(strlen(yytext)+1));
	strncpy(tmp, yytext, strlen(yytext));
	// i used for iterating through tmp
	// j for yytext
	int i, j;
	// flag to indicate if the next character is escaped
	int escaped = 0;
	//NOTE: the space allocated for yytext is the same size as temp
	for (i = 0, j = 0; i < strlen(tmp); ++i) {	
		//skip beginning and terminiating " character
		if (!escaped && tmp[i] == '\"') continue;

		// if a \ character is encountered, set the escaped flag for the next character
		else if (!escaped && tmp[i] == '\\') {
			escaped = 1;
			continue;
		}

		// if it is a "normal" character, add it to yytext
		else if (!escaped) {
			yytext[j] = tmp[i];
			++j;
		} 
		
		// otherwise, it is a character that was just escaped
		else {
			switch(tmp[i]) {
				case 'a': yytext[j] = '\a'; break;
				case 'b': yytext[j] = '\b'; break;
				case 'f': yytext[j] = '\f'; break;
				case 'n': yytext[j] = '\n'; break;
				case 'r': yytext[j] = '\r'; break;
				case 't': yytext[j] = '\t'; break;
				case 'v': yytext[j] = '\v'; break;
				default: yytext[j] = tmp[i]; break;
			}
			++j;
			escaped = 0;
		}
	}
	free(tmp);
	yytext[j] = '\0';
	if (j > 256) return TOKEN_ERROR; //string too long
	return STRING_LITERAL; 
}


.	{ return TOKEN_ERROR; }

%%

