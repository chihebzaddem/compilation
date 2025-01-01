#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "lexer.h"

void checkType(TokenCode type1, TokenCode type2);
void generateCode(char *op);
void parseExpSem(FILE *source);

#endif 
