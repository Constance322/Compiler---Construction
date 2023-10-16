%{
#include "y.tab.h"
%}

%%
[0-9]+          { yylval = atoi(yytext); return NUMBER; }
[-+=*/\n]       { return *yytext; }
[ \t]           ; /* skip whitespace */
.               { return *yytext; }
%%

int yywrap() {
    return 1;
}

/* This defines the lexical analyzer using regular expressions to tokenize 
the input stream into meaningful tokens, which are then used by the parser for further processing.*/

