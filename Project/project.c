#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Token types
typedef enum
{
    TOKEN_EOF,
    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
    TOKEN_COMMA,
    TOKEN_HASH,
    TOKEN_NEWLINE
} TokenType;

// Token structure
typedef struct
{
    TokenType type;
    char value[100]; // Assuming a maximum token length of 100 characters
} Token;

// AST (Abstract Syntax Tree) Node
typedef struct
{
    char operation[100];
    char arg1[100];
    char arg2[100];
} ASTNode;

// Parser state
int currentToken = 0;

// Lexer
Token lexer(char *source, int *pos)
{
    Token token;
    char c = source[(*pos)++];

    while (c == ' ' || c == '\t')
    {
        c = source[(*pos)++];
    }

    if (c == '\0')
    {
        token.type = TOKEN_EOF;
    }
    else if (c == '(')
    {
        token.type = TOKEN_OPEN_PAREN;
    }
    else if (c == ')')
    {
        token.type = TOKEN_CLOSE_PAREN;
    }
    else if (c == ',')
    {
        token.type = TOKEN_COMMA;
    }
    else if (c == '"')
    {
        token.type = TOKEN_STRING;
        int i = 0;
        while (source[(*pos)] != '"')
        {
            token.value[i++] = source[(*pos)++];
        }
        token.value[i] = '\0';
        (*pos)++; // Skip the closing quote
    }
    else if (c == '#')
    {
        token.type = TOKEN_HASH;
    }
    else if (c == '\n')
    {
        token.type = TOKEN_NEWLINE;
    }
    else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        token.type = TOKEN_IDENTIFIER;
        int i = 0;
        while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        {
            token.value[i++] = c;
            c = source[(*pos)++];
        }
        token.value[i] = '\0';
        (*pos)--; // Move back one character to not skip the next character
    }
    else
    {
        while (c != '\0' && c != ' ' && c != '\t' && c != '\n' && c != '\r' && c != '(' && c != ')' && c != ',' && c != '"') 
        {
            c = source[(*pos)++];
        }
        // Call the lexer recursively to get the next non-ignored token
        return lexer(source, pos);
        
    }

    return token;
}

// Parser
Token getNextToken(Token *tokens)
{
    return tokens[currentToken++];
}

ASTNode *parseFileScript(Token *tokens);
ASTNode *parseStatement(Token *tokens);
ASTNode *parseExpression(Token *tokens);
void generateIntermediateCode(ASTNode *root);
void executeIntermediateCode(ASTNode *root);

// Simple runtime
void executeIntermediateCode(ASTNode *root){   
if (root != NULL) {
        if (strcmp(root->operation, "read") == 0) {
            FILE *file = fopen(root->arg1, "r");
            if (file == NULL) {
                perror("Error opening file for read");
                return;
            }

            char buffer[256];
            fread(buffer, sizeof(char), sizeof(buffer), file);
            fclose(file);

            printf("Read from file: %s\n", buffer);
        } else if (strcmp(root->operation, "write") == 0) {
            FILE *file = fopen(root->arg1, "w");
            if (file == NULL) {
                perror("Error opening file for write");
                return;
            }

            fprintf(file, "%s", root->arg2);
            fclose(file);

            printf("Write to file: %s\n", root->arg1);
        }
    }
}


// Parse FileScript
ASTNode *parseFileScript(Token *tokens)
{
    // For simplicity, a script is just a sequence of statements
    return parseStatement(tokens);
}

// Parse Statement
ASTNode *parseStatement(Token *tokens)
{
    Token currentToken = getNextToken(tokens);
    Token nextToken = getNextToken(tokens);

    // Check for read statement
    if (currentToken.type == TOKEN_IDENTIFIER && nextToken.type == TOKEN_OPEN_PAREN)
    {
        ASTNode *readNode = (ASTNode *)malloc(sizeof(ASTNode));
        strcpy(readNode->operation, "read");
        strcpy(readNode->arg1, getNextToken(tokens).value);
        getNextToken(tokens); // consume the closing parenthesis
        return readNode;
    }

    // Check for write statement
    if (currentToken.type == TOKEN_IDENTIFIER && nextToken.type == TOKEN_OPEN_PAREN)
    {
        ASTNode *writeNode = (ASTNode *)malloc(sizeof(ASTNode));
        strcpy(writeNode->operation, "write");
        strcpy(writeNode->arg1, getNextToken(tokens).value);

        // consume the comma
        getNextToken(tokens);

        // read the string argument
        currentToken = getNextToken(tokens);
        if (currentToken.type == TOKEN_STRING)
        {
            strcpy(writeNode->arg2, currentToken.value);
        }

        getNextToken(tokens); // consume the closing parenthesis
        return writeNode;
    }

    
    return NULL; // Invalid statement
}

// Generate Intermediate Code
void generateIntermediateCode(ASTNode *root)
{
    printf("Generated Intermediate Code:\n");

    if (root != NULL) {
        if (strcmp(root->operation, "read") == 0) {
            printf("FILE *file = fopen(\"%s\", \"r\");\n", root->arg1);
            printf("char buffer[256];\n");
            printf("fread(buffer, sizeof(char), sizeof(buffer), file);\n");
            printf("fclose(file);\n");
        } else if (strcmp(root->operation, "write") == 0) {
            printf("FILE *file = fopen(\"%s\", \"w\");\n", root->arg1);
            printf("fprintf(file, \"%s\", \"%s\");\n", root->arg2);
            printf("fclose(file);\n");
        }
    }
}
int main() {
    // Open the script file for reading
    FILE *scriptFile = fopen("myscript.txt", "r");

    // Check if the file was opened successfully
    if (scriptFile == NULL) {
        perror("Error opening script file");
        return 1;
    }

    // Determine the size of the file
    fseek(scriptFile, 0, SEEK_END);
    long scriptSize = ftell(scriptFile);
    rewind(scriptFile);

    // Allocate memory for the script content
    char *script = (char *)malloc(scriptSize + 1);

    // Read the script content into the buffer
    fread(script, 1, scriptSize, scriptFile);
    script[scriptSize] = '\0'; // Null-terminate the string

    // Close the script file
    fclose(scriptFile);

    // Tokenize the script
    int pos = 0;
    Token tokens[100]; // Assuming a maximum of 100 tokens
    int tokenIndex = 0;

    while (1) {
        Token token = lexer(script, &pos);
        tokens[tokenIndex++] = token;

        if (token.type == TOKEN_EOF) {
            break;
        }
    }

    // Parse the script
    ASTNode *root = parseFileScript(tokens);

    // Generate and execute intermediate code
    generateIntermediateCode(root);

    // Clean up memory
    free(script);
    free(root);

    return 0;
}
