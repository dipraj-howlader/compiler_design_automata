#include <stdio.h>
#include <string.h>

char stack[100], input[100], grammar[4][10];
int top = -1, ip = 0;

void shift() {
    stack[++top] = input[ip++];
    stack[top + 1] = '\0';
    printf("Shift:   %-15s Remaining Input: %-15s\n", stack, &input[ip]);
}

int reduce() {
    // E -> i
    if (stack[top] == 'i') {
        stack[top] = 'E';
        printf("Reduce:  E -> i\n");
        return 1;
    }

    // E -> (E)
    if (top >= 2 && stack[top] == ')' && stack[top - 1] == 'E' && stack[top - 2] == '(') {
        stack[top - 2] = 'E';
        top -= 2;
        stack[top + 1] = '\0';
        printf("Reduce:  E -> (E)\n");
        return 1;
    }

    // E -> E+E
    if (top >= 2 && stack[top] == 'E' && stack[top - 1] == '+' && stack[top - 2] == 'E') {
        stack[top - 2] = 'E';
        top -= 2;
        stack[top + 1] = '\0';
        printf("Reduce:  E -> E+E\n");
        return 1;
    }

    // E -> E*E
    if (top >= 2 && stack[top] == 'E' && stack[top - 1] == '*' && stack[top - 2] == 'E') {
        stack[top - 2] = 'E';
        top -= 2;
        stack[top + 1] = '\0';
        printf("Reduce:  E -> E*E\n");
        return 1;
    }

    return 0;
}

int main() {
    printf("Enter 4 grammar rules (e.g., E=E+E):\n");
    for (int i = 0; i < 4; i++) {
        printf("Production %d: ", i + 1);
        scanf("%s", grammar[i]);
    }

    printf("\nLoaded Grammar:\n");
    for (int i = 0; i < 4; i++) {
        printf("%s\n", grammar[i]);
    }

    printf("\nEnter input string (use 'i' for id): ");
    scanf("%s", input);

    printf("\nParsing Steps:\n");

    while (input[ip] != '\0') {
        shift();

        while (reduce())
            ;
    }

    while (reduce())
        ;

    if (strcmp(stack, "E") == 0) {
        printf("\nSuccess: Input string is accepted by the grammar.\n");
    } else {
        printf("\nError: Input string is rejected by the grammar.\n");
    }

    return 0;
}

/*
E=E+E
E=E*E
E=(E)
E=i

Enter input string: i+i*i



*/