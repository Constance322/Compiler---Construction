#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function declarations
int expression();
int term();
int factor();

// Global variables
char *input;
char lookahead;

// Error function
void error() {
    fprintf(stderr, "Error\n");
    exit(1);
}

// Advance the input to the next character
void next() {
    lookahead = *input++;
}

// Match a specific character
void match(char c) {
    if (lookahead == c) {
        next();
    } else {
        error();
    }
}

// Parse the expression
int expression() {
    int result = term();
    while (lookahead == '+' || lookahead == '-') {
        char op = lookahead;
        next();
        if (op == '+') {
            result += term();
        } else if (op == '-') {
            result -= term();
        }
    }
    return result;
}

// Parse the term
int term() {
    int result = factor();
    while (lookahead == '*' || lookahead == '/') {
        char op = lookahead;
        next();
        if (op == '*') {
            result *= factor();
        } else if (op == '/') {
            result /= factor();
        }
    }
    return result;
}

// Parse the factor
int factor() {
    int result;
    if (isdigit(lookahead)) {
        result = lookahead - '0';
        next();
    } else if (lookahead == '(') {
        match('(');
        result = expression();
        match(')');
    } else {
        error();
    }
    return result;
}

int main() {
    printf("Enter an arithmetic expression: ");
    char buf[100];
    fgets(buf, sizeof(buf), stdin);
    input = buf;
    next();
    printf("Result: %d\n", expression());
    return 0;
}
/* This file contains the code responsible for parsing expressions based on the precedence of operators, 
ensuring that the expressions are evaluated correctly according to the defined precedence rules.*/
