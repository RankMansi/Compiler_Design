%option noyywrap
%{
#include <stdio.h>

int count_kw=0;
int count_identifiers=0;
int count_num=0;

%}

%%

int|float|double|switch                         {count_kw++; printf("%s is a Keyword with length: %d\n", yytext, yyleng);}
[a-zA-Z][a-zA-Z0-9]*                            {count_identifiers++; printf("%s is an Identifier with length: %d\n", yytext, yyleng);}
-?(([0-9]+)|([0-9]*\.[0-9]+))([eE][-+]?[0-9]+)? {count_num++; printf("%s is a Number with length: %d\n", yytext, yyleng);}


%%

int main() {
    yylex();
    printf("Total keywords are: %d\n", count_kw);
    printf("Total identifiers are: %d\n", count_identifiers);
    printf("Total numbers are: %d\n", count_num);
    return 0;
}