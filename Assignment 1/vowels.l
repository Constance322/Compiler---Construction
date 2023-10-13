/*Declaration*/
%{
int count_a = 0;
int count_e = 0;
int count_i = 0;
int count_o = 0;
int count_u = 0;
int count_non_vowel = 0;

%}
 
/*** Rule Section ***/
%%

[aA]+ {count_a++;} // matches one or more vowels present
[eE]+ {count_e++;}
[iI]+ {count_i++;}
[oO]+ {count_o++;}
[uU]+ {count_u++;}

. ; // any other characters are ignored

\n    {return 0;} // a newline means the end of the input
%%
 
/*** Code Section prints the number of vowels present***/
int yywrap(){}
int main(){
 
yylex();
printf("\n Occurrences of 'A':%d\n" , count_a);
printf("\n Occurrences of 'E':%d\n" , count_e);
printf("\n Occurrences of 'I':%d\n" , count_i);
printf("\n Occurrences of 'O':%d\n" , count_o);
printf("\n Occurrences of 'U':%d\n" , count_u);

return 0;
}