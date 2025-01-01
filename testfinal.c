#include "lexer.h"
#include "parser.h"
#include "semantic.h"
#include <stdio.h>
#include <assert.h>

// Helper function to create and write a test input file
void createTestFile(const char *filename, const char *content) {
    FILE *source = fopen(filename, "w");
    if (!source) {
        printf("Error opening file %s for writing\n", filename);
        exit(1);
    }
    fprintf(source, "%s", content);
    fclose(source);
}

// Test function for lexical analyzer
void testLexer() {
    printf("Running Lexer Tests...\n");

    const char *testInput = "program test; var x, y: int; begin x := 10; end.";
    createTestFile("test_input.txt", testInput);

    FILE *source = fopen("test_input.txt", "r");
    if (!source) {
        printf("Error opening test file for reading\n");
        exit(1);
    }

    Token token;
    
    // Test tokens
    token = getNextToken(source);
    assert(token.code == TOKEN_PROGRAM && "Expected TOKEN_PROGRAM");
    assert(strcmp(token.lexeme, "program") == 0);

    token = getNextToken(source);
    assert(token.code == TOKEN_ID && "Expected TOKEN_ID");
    assert(strcmp(token.lexeme, "test") == 0);

    token = getNextToken(source);
    assert(token.code == TOKEN_SEMICOLON);

    token = getNextToken(source);
    assert(token.code == TOKEN_VAR);

    token = getNextToken(source);
    assert(token.code == TOKEN_ID && "Expected TOKEN_ID for 'x'");
    assert(strcmp(token.lexeme, "x") == 0);

    token = getNextToken(source);
    assert(token.code == TOKEN_COMMA);

    token = getNextToken(source);
    assert(token.code == TOKEN_ID && "Expected TOKEN_ID for 'y'");
    assert(strcmp(token.lexeme, "y") == 0);

    token = getNextToken(source);
    assert(token.code == TOKEN_COLON);

    token = getNextToken(source);
    assert(token.code == TOKEN_INT);

    token = getNextToken(source);
    assert(token.code == TOKEN_SEMICOLON);

    token = getNextToken(source);
    assert(token.code == TOKEN_BEGIN);

    token = getNextToken(source);
    assert(token.code == TOKEN_ID && "Expected TOKEN_ID for 'x'");
    assert(strcmp(token.lexeme, "x") == 0);

    token = getNextToken(source);
    assert(token.code == TOKEN_ASSIGN);

    token = getNextToken(source);
    assert(token.code == TOKEN_NB && "Expected TOKEN_NB for number");
    assert(strcmp(token.lexeme, "10") == 0);

    token = getNextToken(source);
    assert(token.code == TOKEN_SEMICOLON);

    token = getNextToken(source);
    assert(token.code == TOKEN_END);

    token = getNextToken(source);
    assert(token.code == TOKEN_DOT);

    token = getNextToken(source);
    assert(token.code == TOKEN_EOF);

    fclose(source);
    printf("Lexer Tests Passed!\n");
}

// Test function for syntax analyzer
void testParser() {
    printf("Running Parser Tests...\n");

    const char *testInput = "program test; var x, y: int; begin x := 10; end.";
    createTestFile("test_input.txt", testInput);

    FILE *source = fopen("test_input.txt", "r");
    if (!source) {
        printf("Error opening test file for reading\n");
        exit(1);
    }

    lookahead = getNextToken(source);

    // Test parsing
    parseProgram(source);

    // Ensure the entire input is consumed
    assert(lookahead.code == TOKEN_EOF);

    fclose(source);
    printf("Parser Tests Passed!\n");
}

// Test function for semantic analyzer
void testSemantic() {
    printf("Running Semantic Tests...\n");

    const char *testInput = "program test; var x, y: int; begin x := 10; y := x + 5; end.";
    createTestFile("test_input.txt", testInput);

    FILE *source = fopen("test_input.txt", "r");
    if (!source) {
        printf("Error opening test file for reading\n");
        exit(1);
    }

    lookahead = getNextToken(source);

    // Test parsing and semantic checks
    parseProgram(source);

    // Ensure the entire input is consumed
    assert(lookahead.code == TOKEN_EOF);

    fclose(source);
    printf("Semantic Tests Passed!\n");
}

int main() {
    testLexer();
    testParser();
    testSemantic();
    printf("All tests passed!\n");
    return 0;
}
