#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char input[100];
int i = 0;

void E();
void EPrime();
void T();
void TPrime();
void F();

void error() {
    printf("Error: Invalid syntax!\n");
    exit(1);
}

void match(char expected) {
    if (input[i] == expected) {
        i++;
    } else {
        error();
    }
}

void E() {
    T();
    EPrime();
}

void EPrime() {
    if (input[i] == '+') {
        match('+');
        T();
        EPrime();
    }
    // else ε (do nothing)
}

void T() {
    F();
    TPrime();
}

void TPrime() {
    if (input[i] == '*') {
        match('*');
        F();
        TPrime();
    }
    // else ε (do nothing)
}

void F() {
    if (input[i] == '(') {
        match('(');
        E();
        match(')');
    } else if (input[i] == 'i') { // assume 'i' represents id
        match('i');
    } else {
        error();
    }
}

int main() {
    printf("Enter the expression (use 'i' for id): ");
    scanf("%s", input);

    strcat(input, "$"); // End marker

    E();

    if (input[i] == '$') {
        printf("Accepted: Valid expression.\n");
    } else {
        printf("Rejected: Extra symbols after parsing.\n");
    }

    return 0;
}



//(i+i)*i
// i+*i
