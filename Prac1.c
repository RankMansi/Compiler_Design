#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *keywords[] = {
    "int", "return", "if", "else", "while", "for", "do", "break", "continue",
    "char", "float", "double", "void", "static", "const", "sizeof", "switch",
    "case", "default", "struct", "union", "typedef", "enum", "extern", "volatile", "main"
};
const char *operators[] = {
    "+", "-", "*", "/", "%", "++", "--", "=", "+=", "-=", "*=", "/=", "==", "!=", ">", "<", ">=", "<=",
    "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", ">>>", "?", ":", ".", "->"
};

const char *delimiters = " \t\n{}[]()<>;,";

#define KEYWORD_COUNT (sizeof(keywords) / sizeof(keywords[0]))
#define OPERATOR_COUNT (sizeof(operators) / sizeof(operators[0]))

int isKeyword(const char *word) {
    for (int i = 0; i < KEYWORD_COUNT; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isOperator(const char *word) {
    for (int i = 0; i < OPERATOR_COUNT; i++) {
        if (strcmp(word, operators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isIdentifier(const char *word) {
    if ((!isalpha(word[0]) && word[0] != '_')) {
        return 0;
    }
    for (int i = 1; word[i] != '\0'; i++) {
        if (!isalnum(word[i]) && word[i] != '_') {
            return 0;
        }
    }
    return 1;
}

int isNumber(const char *word) {
    if (word[0] == '\0') return 0;
    char *endptr;
    strtol(word, &endptr, 10);
    return *endptr == '\0';
}

void analyze(const char *word) {
    if (isKeyword(word)) {
        printf("Token: %s   Type: KEYWORD\n", word);
    } else if (isOperator(word)) {
        printf("Token: %s   Type: OPERATOR\n", word);
    } else if (isIdentifier(word)) {
        printf("Token: %s   Type: IDENTIFIER\n", word);
    } else if (isNumber(word)) {
        printf("Token: %s   Type: LITERAL (NUMBER)\n", word);
    } else if (word[0] == '"' || word[0] == '\'') {
        printf("Token: %s   Type: LITERAL (STRING)\n", word);
    } else {
        printf("Token: %s   Type: DELIMITER\n", word);
    }
}

void processFile(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char buffer[256];
        int bufferIndex = 0;
        int flag = 0;  // Flag to check if we're inside a string literal

        for (int i = 0; i < strlen(line); i++) {
            if (line[i] == '"' || line[i] == '\'') {
                if (flag) {
                    // End of string literal
                    buffer[bufferIndex++] = line[i];
                    buffer[bufferIndex] = '\0';
                    analyze(buffer);
                    bufferIndex = 0;
                    flag = 0;
                } else {
                    // Start of string literal
                    if (bufferIndex != 0) {
                        buffer[bufferIndex] = '\0';
                        analyze(buffer);
                        bufferIndex = 0;
                    }
                    buffer[bufferIndex++] = line[i];
                    flag = 1;
                }
            } else if (isspace(line[i]) || strchr(delimiters, line[i]) != NULL) {
                if (bufferIndex != 0) {
                    buffer[bufferIndex] = '\0';
                    analyze(buffer);
                    bufferIndex = 0;
                }
                if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') {
                    char delim[2] = {line[i], '\0'};
                    analyze(delim);
                }
            } else {
                buffer[bufferIndex++] = line[i];
            }
        }
        if (bufferIndex != 0) {
            buffer[bufferIndex] = '\0';
            analyze(buffer);
        }
    }

    fclose(file);
}

int main() {
    const char *filePath = "D:\\Projects\\RankMansi\\Semesters\\Sem-5\\Lab-Compiler Design\\1_Practical.txt";
    processFile(filePath);
    return 0;
}