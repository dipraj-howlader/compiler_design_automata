#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// List of C keywords
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

// Function to check if a word is a C keyword
bool isKeyword(const char *word) {
    int n = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Function to check if a string is a valid identifier
bool isValidIdentifier(const char *str) {
    // Check if empty
    if (str[0] == '\0') return false;

    // First character must be letter or underscore
    if (!(isalpha(str[0]) || str[0] == '_')) {
        return false;
    }

    // Check remaining characters
    for (int i = 1; str[i] != '\0'; i++) {
        if (!(isalnum(str[i]) || str[i] == '_')) {
            return false;
        }
    }

    // Cannot be a keyword
    if (isKeyword(str)) {
        return false;
    }

    return true;
}

int main() {
    char str[100];

    while(1) {
    printf("Enter a string: ");
    scanf("%s", str);

    if (isValidIdentifier(str)) {
        printf("'%s' is a valid identifier.\n", str);
    } else {
        printf("'%s' is NOT a valid identifier.\n", str);
    }
    }
    return 0;
}



// int
// _var
// 9data
// myVar1
// @temp	