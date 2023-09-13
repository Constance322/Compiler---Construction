%{
#include <stdio.h>
%}

%%
[a-zA-Z]+   { printf("%s\n", yytext); }  // Match words and print them
.|\n        ;  // Ignore other characters

%%

int main(int argc, char *argv[]) {
    yyin = stdin;  // Read from stdin
    yylex();      // Start lexical analysis
    return 0;
}
