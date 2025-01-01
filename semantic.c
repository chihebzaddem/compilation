#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h> 
#include "parser.h" 

void checkType(TokenCode type1, TokenCode type2) {
    if (type1 != type2) {
        printf("Type mismatch error\n");
        exit(1);
    }
}

void generateCode(char *op) {
    printf("Generate code for %s\n", op);
}

void parseExpSem(FILE *source) {
    if (lookahead.code == TOKEN_ID || lookahead.code == TOKEN_NB) {
        TokenCode type = lookahead.code;
        match(lookahead.code, source);
        generateCode("push");
        if (lookahead.code == TOKEN_OPARITH) {
            char *op = lookahead.lexeme;
            match(TOKEN_OPARITH, source);
            parseExpSem(source);
            generateCode(op);
        }
    } else if (lookahead.code == TOKEN_LPAREN) {
        match(TOKEN_LPAREN, source);
        parseExpSem(source);
        match(TOKEN_RPAREN, source);
    } else {
        printf("Syntax error: unexpected token %s\n", lookahead.lexeme);
        exit(1);
    }
}
