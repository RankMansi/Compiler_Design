%option noyywrap
%{
#include <stdio.h>

int blank = 0, tabs = 0, newline = 0;

%}

%%

int|float|double|switch                         {printf("%s is a Keyword with length: %d\n", yytext, yyleng);}
[a-zA-Z][a-zA-Z0-9]*                            {printf("%s is an Identifier with length: %d\n", yytext, yyleng);}
-?(([0-9]+)|([0-9]*\.[0-9]+))([eE][-+]?[0-9]+)? {printf("%s is a Number with length: %d\n", yytext, yyleng);}

[ \t\n] {
    // Count blanks, tabs, and newlines
    if (yytext[0] == ' ') blank++;
    else if (yytext[0] == '\t') tabs++;
    else if (yytext[0] == '\n') newline++;
}
. {
    // Match any other character but do nothing
}

%%

int main() {
    yylex();
    printf("Number of blanks: %d\n", blank);
    printf("Number of tabs: %d\n", tabs);
    printf("Number of newlines: %d\n", newline);
    return 0;
}