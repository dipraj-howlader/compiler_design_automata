#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *input;
int pos = 0;

void error() {
    printf("Error: Invalid string at position %d ('%c')\n", pos, input[pos]);
    exit(1);
}

void match(char expected) {
    if (input[pos] == expected) {
        pos++;
    } else {
        error();
    }
}

// Grammar:
// S → a S b
//    | a b
void S() {
    if (input[pos] == 'a') {
        match('a');

        if (input[pos] == 'a') {
            S();
            match('b');
        } else if (input[pos] == 'b') {
            match('b');
        } else {
            error();
        }
    } else {
        error();
    }
}

int main() {
    char production1[20], production2[20];
    char buffer[100];

    // Step 1: Input grammar (for formality, but we use hardcoded logic)
    printf("Enter production 1 (e.g., S=aSb): ");
    scanf("%s", production1);
    printf("Enter production 2 (e.g., S=ab): ");
    scanf("%s", production2);

    printf("\nGrammar Loaded:\n%s\n%s\n", production1, production2);

    // Step 2: Input string to parse
    printf("\nEnter input string (only a's and b's): ");
    scanf("%s", buffer);

    input = buffer;

    S();  // Call starting symbol

    if (input[pos] == '\0') {
        printf("Success: Input string is valid under the grammar.\n");
    } else {
        printf("Error: Extra characters after parsing.\n");
    }

    return 0;
}


/*

S = aSb
S=ab


aaabbb
aabb


not valid

aaaabbbb


*/