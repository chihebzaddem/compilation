#include "lexer.h"
#include "parser.h"
#include "semantic.h"

int main(int argc, char *argv[]) {
    // Check if the user has provided a source file as an argument
    if (argc < 2) {
        printf("Usage: %s <source file>\n", argv[0]);
        return 1;
    }

    // Open the source file
    FILE *source = fopen(argv[1], "r");
    if (!source) {
        printf("Error opening file %s\n", argv[1]);
        return 1;
    }

    // Initialize the first token
    lookahead = getNextToken(source);

    // Parse the program
    parseProgram(source);

    // Check for unexpected tokens after parsing
    if (lookahead.code != TOKEN_EOF) {
        printf("Syntax error: unexpected token %s\n", lookahead.lexeme);
        fclose(source);
        return 1;
    }

    // Parsing completed successfully
    printf("Parsing completed successfully.\n");

    // Close the source file
    fclose(source);
    return 0;
}
