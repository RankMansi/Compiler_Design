%option noyywrap
%{
#include <stdio.h>

FILE *inputFile;
FILE *outputFile;
%}

%%
"//".*               ;  /* Ignore single-line comments */
"/*"(.|\n)*?"*/"     ;  /* Ignore multi-line comments */
.|\n                 { fprintf(outputFile, "%s", yytext); }  /* Write everything else to the output file */
%%

int main() {

    inputFile = fopen("input_with_comments.txt", "r");
    if (!inputFile) {
        perror("Error opening input file");
        return 1;
    }

    outputFile = fopen("output_without_comments.txt", "w");
    if (!outputFile) {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }

    yyin = inputFile;
    yylex();

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}