#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LEN 100

// Enum to define the possible token codes
typedef enum {
    TOKEN_PROGRAM, TOKEN_ID, TOKEN_SEMICOLON, TOKEN_VAR, TOKEN_COLON, TOKEN_INT,
    TOKEN_BEGIN, TOKEN_END, TOKEN_DOT, TOKEN_COMMA, TOKEN_ASSIGN, TOKEN_WRITELN,
    TOKEN_READLN, TOKEN_IF, TOKEN_THEN, TOKEN_ENDIF, TOKEN_OPREL, TOKEN_OPARITH,
    TOKEN_NB, TOKEN_LPAREN, TOKEN_RPAREN, TOKEN_EOF, TOKEN_ERROR
} TokenCode;

// Structure for a Token
typedef struct {
    TokenCode code;       // The type of token
    char lexeme[MAX_TOKEN_LEN]; // The actual string representing the token
} Token;

// Function declarations
Token getNextToken(FILE *source);
int isKeyword(const char *str); 

#endif
