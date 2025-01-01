#include "lexer.h"

Token getNextToken(FILE *source) {
    Token token;
    char ch;
    int i = 0;

    // Skip whitespace
    skipWhitespace(source);

    if ((ch = fgetc(source)) == EOF) {
        token.code = TOKEN_EOF;
        return token;
    }

    // Identifiers and keywords
    if (isalpha(ch)) {
        token = handleIdentifierOrKeyword(source, ch);
        return token;
    }

    // Numbers
    if (isdigit(ch)) {
        token = handleNumber(source, ch);
        return token;
    }

    // Operators and punctuation
    token = handleOperatorsAndPunctuation(source, ch, i);
    return token;
}

void skipWhitespace(FILE *source) {
    char ch;
    while ((ch = fgetc(source)) == ' ' || ch == '\n' || ch == '\t');
    ungetc(ch, source);
}

Token handleIdentifierOrKeyword(FILE *source, char ch) {
    Token token;
    int i = 0;
    token.lexeme[i++] = ch;

    // Read full identifier or keyword
    while (isalnum(ch = fgetc(source))) {
        token.lexeme[i++] = ch;
    }
    token.lexeme[i] = '\0';
    ungetc(ch, source);

    if (isKeyword(token.lexeme)) {
        token.code = getKeywordToken(token.lexeme);
    } else {
        token.code = TOKEN_ID;
    }

    return token;
}

int getKeywordToken(char *lexeme) {
    if (strcmp(lexeme, "program") == 0) return TOKEN_PROGRAM;
    if (strcmp(lexeme, "var") == 0) return TOKEN_VAR;
    if (strcmp(lexeme, "int") == 0) return TOKEN_INT;
    if (strcmp(lexeme, "begin") == 0) return TOKEN_BEGIN;
    if (strcmp(lexeme, "end") == 0) return TOKEN_END;
    if (strcmp(lexeme, "writeln") == 0) return TOKEN_WRITELN;
    if (strcmp(lexeme, "readln") == 0) return TOKEN_READLN;
    if (strcmp(lexeme, "if") == 0) return TOKEN_IF;
    if (strcmp(lexeme, "then") == 0) return TOKEN_THEN;
    if (strcmp(lexeme, "endif") == 0) return TOKEN_ENDIF;
    return -1; // If not found, return an invalid token
}

Token handleNumber(FILE *source, char ch) {
    Token token;
    int i = 0;
    token.lexeme[i++] = ch;

    while (isdigit(ch = fgetc(source))) {
        token.lexeme[i++] = ch;
    }
    token.lexeme[i] = '\0';
    ungetc(ch, source);

    token.code = TOKEN_NB;
    return token;
}

Token handleOperatorsAndPunctuation(FILE *source, char ch, int i) {
    Token token;
    char nextCh;

    switch (ch) {
        case ';': token.code = TOKEN_SEMICOLON; break;
        case ':':
            nextCh = fgetc(source);
            if (nextCh == '=') {
                token.code = TOKEN_ASSIGN;
                token.lexeme[i++] = ch;
                token.lexeme[i++] = nextCh;
            } else {
                ungetc(nextCh, source);
                token.code = TOKEN_COLON;
                token.lexeme[i++] = ch;
            }
            break;
        case ',': token.code = TOKEN_COMMA; break;
        case '.': token.code = TO
