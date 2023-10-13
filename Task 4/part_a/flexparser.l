%{
#include <stdio.h>
int yylex();
void yyerror(const char *s);
%}

%token WORD NUMBER

%%

input: /* empty */
     | input line
     ;

line: WORD '\n' { printf("Found a word: %s\n", $1); }
    | NUMBER '\n' { printf("Found a number: %s\n", $1); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    yyparse();
    return 0;
}
