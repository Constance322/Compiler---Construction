%{
#include <stdio.h>
%}

%token NUMBER

%%
input: /* empty */
     | input line
     ;

line: '\n'
     | exp '\n' { printf("Result: %d\n", $1); }
     ;

exp: NUMBER
     | exp '+' exp { $$ = $1 + $3; }
     | exp '-' exp { $$ = $1 - $3; }
     ;

%%

int main() {
    yyparse();
    return 0;
}

int yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}


/*this file contains the grammar rules and associated actions for constructing the parser, 
defining how input expressions are recognized and processed.*/ 
