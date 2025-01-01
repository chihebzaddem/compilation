#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

void match(TokenCode expected) {
    if (lookahead.code == expected) {
        lookahead = getNextToken(source);
    } else {
        printf("Syntax error: unexpected token %s\n", lookahead.lexeme);
        exit(1);
    }
}

void parseProgram() {
    match(TOKEN_PROGRAM);
    match(TOKEN_ID);
    match(TOKEN_SEMICOLON);
    parseDcl();
    match(TOKEN_BEGIN);
    parseListe_inst();
    match(TOKEN_END);
    match(TOKEN_DOT);
}

void parseDcl() {
    if (lookahead.code == TOKEN_VAR) {
        match(TOKEN_VAR);
        parseListe_id();
        match(TOKEN_COLON);
        match(TOKEN_INT);
        match(TOKEN_SEMICOLON);
    }
}

void parseListe_id() {
    match(TOKEN_ID);
    while (lookahead.code == TOKEN_COMMA) {
        match(TOKEN_COMMA);
        match(TOKEN_ID);
    }
}

void parseListe_inst() {
    if (lookahead.code == TOKEN_ID || lookahead.code == TOKEN_Writeln || lookahead.code == TOKEN_Readln || lookahead.code == TOKEN_IF) {
        parseI();
        parseListe_inst();
    }
}

void parseI() {
    if (lookahead.code == TOKEN_ID) {
        match(TOKEN_ID);
        match(TOKEN_ASSIGN);
        parseExp();
        match(TOKEN_SEMICOLON);
    } else if (lookahead.code == TOKEN_Writeln) {
        match(TOKEN_Writeln);
        match(TOKEN_LPAREN);
        match(TOKEN_ID);
        match(TOKEN_RPAREN);
        match(TOKEN_SEMICOLON);
    } else if (lookahead.code == TOKEN_Readln) {
        match(TOKEN_Readln);
        match(TOKEN_LPAREN);
        match(TOKEN_ID);
        match(TOKEN_RPAREN);
        match(TOKEN_SEMICOLON);
    } else if (lookahead.code == TOKEN_IF) {
        match(TOKEN_IF);
        parseExp();
        match(TOKEN_THEN);
        parseListe_inst();
        match(TOKEN_END);
    }
}

void parseExp() {
    if (lookahead.code == TOKEN_ID) {
        match(TOKEN_ID);
    } else if (lookahead.code == TOKEN_NB) {
        match(TOKEN_NB);
    } else if (lookahead.code == TOKEN_LPAREN) {
        match(TOKEN_LPAREN);
        parseExp();
        match(TOKEN_RPAREN);
    } else {
        printf("Syntax error in expression\n");
        exit(1);
    }

    if (lookahead.code == TOKEN_OPARITH) {
        match(TOKEN_OPARITH);
        parseExp();
    }
}

