#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Check if input is a valid operator
bool isValidOperator(const char *op) {
    const char *validOperators[] = {
        "+", "-", "*", "/", "%",       // Arithmetic
        "++", "--",                    // Increment/Decrement
        "==", "!=", ">", "<", ">=", "<=", // Relational
        "&&", "||", "!",               // Logical
        "&", "|", "^", "~", "<<", ">>", // Bitwise
        "=", "+=", "-=", "*=", "/=", "%=" // Assignment
    };
    int n = sizeof(validOperators) / sizeof(validOperators[0]);

    for (int i = 0; i < n; i++) {
        if (strcmp(op, validOperators[i]) == 0)
            return true;
    }
    return false;
}

int main() {
    char input[10];

    printf("Enter an operator: ");
    scanf("%s", input);

    if (isValidOperator(input)) {
        printf("%s is a valid operator.\n", input);
    } else {
        printf("%s is NOT a valid operator.\n", input);
    }

    return 0;
}
