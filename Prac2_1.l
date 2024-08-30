%option noyywrap
%{
#include <stdio.h>
int count_kw=0;
int count_identifiers=0;
int count_num=0;
int tot_tokens;
%}

%%
int|float|double|switch	                          {count_kw++; printf("%s is Keyword\n",yytext);}
[a-zA-Z][a-zA-Z0-9]*                              {count_identifiers++; printf("%s is an Identifier\n",yytext);}
-?((([0-9]+)|([0-9]*\.[0-9]+))([eE][-+]?[0-9]+)?) {count_num++; printf("%s is a Number\n",yytext);}
%%

int main()
{
    yylex();
    printf("Total keywords are: %d\n", count_kw);
    printf("Total identifiers are: %d\n", count_identifiers);
    printf("Total numbers are: %d\n", count_num);
    tot_tokens = count_kw + count_identifiers + count_num;
    printf("Total tokens are: %d\n", tot_tokens);
    return 0;
}