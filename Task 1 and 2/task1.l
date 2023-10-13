%{


int is_comment =0; // boolean to show if it is a comment


struct token{
char *type; // comment or code
char *value; // text of the code
};

struct token *make_token(char *type, char *value){

struct token *token =  malloc(sizeof(struct token));
token->type = type;
token->value = value;
return token;
}

%}

%%
\/\/[^\n]*     { printf("Single-line comment: %s\n", yytext); }
\/\*[^*]*\*+([^/*][^*]*\*+)*\/ { printf("Multi-line comment: %s\n", yytext); }
.              { printf("Code: %s\n", yytext); }

{
if (is_comment = 0); 
{

printf("code: %l\n", yytext);
}
} 

%%
int main(){
yylex();
return 0;
}