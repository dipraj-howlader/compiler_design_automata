#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[100];
int i = 0;

// Function declarations for non-terminals
void E();
void EPrime();
void T();
void TPrime();
void F();

void error() {
    printf("❌ Syntax Error at position %d!\n", i);
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
    // else ε (do nothing)
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
    // else ε (do nothing)
}

// F → (E) | id
void F() {
    if (input[i] == '(') {
        match('(');
        E();
        match(')');
    } else if (input[i] == 'i') { // 'i' for id
        match('i');
    } else {
        error();
    }
}

int main() {
    printf("Enter expression (use 'i' for identifier): ");
    scanf("%s", input);

    strcat(input, "$"); // Add end marker

    E(); // Start parsing

    if (input[i] == '$') {
        printf("✅ Parsing successful: Valid expression.\n");
    } else {
        printf("❌ Parsing failed: Extra input remaining.\n");
    }

    return 0;
}
