#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LEN 64

typedef enum {
    TOKEN_PROGRAM, TOKEN_VAR, TOKEN_ID, TOKEN_SEMICOLON, TOKEN_COLON, TOKEN_INT,
    TOKEN_ASSIGN, TOKEN_NB, TOKEN_BEGIN, TOKEN_END, TOKEN_IF, TOKEN_THEN, 
    TOKEN_Writeln, TOKEN_Readln, TOKEN_OPREL, TOKEN_OPARITH, TOKEN_COMMA, 
    TOKEN_DOT, TOKEN_EOF, TOKEN_LPAREN, TOKEN_RPAREN, TOKEN_ERROR
} TokenCode;

typedef struct {
    TokenCode code;
    char lexeme[MAX_TOKEN_LEN];
} Token;

Token lookahead;

FILE *source;
int currentChar;

void skipWhitespace() {
    while (isspace(currentChar) || currentChar == '\n') {
        currentChar = fgetc(source);
    }
}

Token getNextToken(FILE *source) {
    Token token;
    token.lexeme[0] = '\0'; // Clear lexeme buffer

    skipWhitespace();

    if (currentChar == EOF) {
        token.code = TOKEN_EOF;
        return token;
    }

    if (isalpha(currentChar)) { // identifier (id)
        int i = 0;
        while (isalnum(currentChar) || currentChar == '_') {
            token.lexeme[i++] = currentChar;
            currentChar = fgetc(source);
        }
        token.lexeme[i] = '\0';
        if (strcmp(token.lexeme, "program") == 0) {
            token.code = TOKEN_PROGRAM;
        } else if (strcmp(token.lexeme, "var") == 0) {
            token.code = TOKEN_VAR;
        } else if (strcmp(token.lexeme, "begin") == 0) {
            token.code = TOKEN_BEGIN;
        } else if (strcmp(token.lexeme, "end") == 0) {
            token.code = TOKEN_END;
        } else if (strcmp(token.lexeme, "if") == 0) {
            token.code = TOKEN_IF;
        } else if (strcmp(token.lexeme, "then") == 0) {
            token.code = TOKEN_THEN;
        } else if (strcmp(token.lexeme, "writeln") == 0) {
            token.code = TOKEN_Writeln;
        } else if (strcmp(token.lexeme, "readln") == 0) {
            token.code = TOKEN_Readln;
        } else {
            token.code = TOKEN_ID;
        }
    } else if (isdigit(currentChar)) { // number (nb)
        int i = 0;
        while (isdigit(currentChar)) {
            token.lexeme[i++] = currentChar;
            currentChar = fgetc(source);
        }
        token.lexeme[i] = '\0';
        token.code = TOKEN_NB;
    } else if (currentChar == ':') { // colon
        token.code = TOKEN_COLON;
        currentChar = fgetc(source);
    } else if (currentChar == ';') { // semicolon
        token.code = TOKEN_SEMICOLON;
        currentChar = fgetc(source);
    } else if (currentChar == '=' || currentChar == '<' || currentChar == '>' || currentChar == '!') { // relational operators
        char op = currentChar;
        token.lexeme[0] = op;
        currentChar = fgetc(source);
        if (op == '<' && currentChar == '>') {
            token.lexeme[1] = currentChar;
            token.lexeme[2] = '\0';
            token.code = TOKEN_OPREL;
            currentChar = fgetc(source);
        } else if (op == '=') {
            token.code = TOKEN_OPREL;
        } else if (op == '<' || op == '>') {
            token.code = TOKEN_OPREL;
        } else if (op == '!') {
            token.code = TOKEN_OPREL;
        }
    } else if (currentChar == '+' || currentChar == '*') { // arithmetic operators
        token.lexeme[0] = currentChar;
        token.lexeme[1] = '\0';
        token.code = TOKEN_OPARITH;
        currentChar = fgetc(source);
    } else if (currentChar == '.') { // dot
        token.code = TOKEN_DOT;
        currentChar = fgetc(source);
    } else if (currentChar == ',') { // comma
        token.code = TOKEN_COMMA;
        currentChar = fgetc(source);
    } else if (currentChar == '(') { // left parenthesis
        token.code = TOKEN_LPAREN;
        currentChar = fgetc(source);
    } else if (currentChar == ')') { // right parenthesis
        token.code = TOKEN_RPAREN;
        currentChar = fgetc(source);
    } else {
        token.code = TOKEN_ERROR;
    }

    return token;
}

void initializeLexer(FILE *sourceFile) {
    source = sourceFile;
    currentChar = fgetc(source);
}

