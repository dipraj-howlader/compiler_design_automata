#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[100];
int i = 0;

// Forward declarations
void E();
void EPrime();
void T();
void TPrime();
void F();

void error() {
    printf("❌ Syntax Error at position %d\n", i);
    exit(1);
}

void match(char expected) {
    if (input[i] == expected) {
        i++;
    } else {
        error();
    }
}

// E → T E'
void E() {
    T();
    EPrime();
}

// E' → + T E' | ε
void EPrime() {
    if (input[i] == '+') {
        match('+');
        T();
        EPrime();
    }
    // else epsilon (do nothing)
}

// T → F T'
void T() {
    F();
    TPrime();
}

// T' → * F T' | ε
void TPrime() {
    if (input[i] == '*') {
        match('*');
        F();
        TPrime();
    }
    // else epsilon (do nothing)
}

// F → ( E ) | i
void F() {
    if (input[i] == '(') {
        match('(');
        E();
        match(')');
    } else if (input[i] == 'i') {
        match('i');
    } else {
        error();
    }
}

int main() {
    printf("Enter an expression (use 'i' for id): ");
    scanf("%s", input);

    strcat(input, "$"); // End marker

    E(); // Start parsing

    if (input[i] == '$') {
        printf("✅ Parsing successful: Valid expression\n");
    } else {
        printf("❌ Parsing failed: Unexpected extra input\n");
    }

    return 0;
}
