#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// Function declarations for parsing
void parseProgram(FILE *source);
void parseDel(FILE *source);
void parseListe_id(FILE *source);
void parseListe_inst(FILE *source);
void parseI(FILE *source);
void parseC(FILE *source);
void parseExp(FILE *source);

// Match the expected token
void match(TokenCode expected, FILE *source);

// Global lookahead token
extern Token lookahead;

#endif
