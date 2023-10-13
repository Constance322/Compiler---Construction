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

