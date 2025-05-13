#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char postfix[MAX];
int tempCount = 1;

// Stack for postfix conversion
char stack[MAX];
int top = -1;

void push(char ch) {
    stack[++top] = ch;
}

char pop() {
    return (top == -1) ? '\0' : stack[top--];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Convert infix to postfix
void infixToPostfix(char *infix) {
    int j = 0;
    for (int i = 0; infix[i]; i++) {
        char ch = infix[i];
        if (isspace(ch)) continue;

        if (isalnum(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(ch);
        } else if (ch == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[j++] = pop();
            pop(); // remove '('
        } else { // operator
            while (top != -1 && precedence(stack[top]) >= precedence(ch))
                postfix[j++] = pop();
            push(ch);
        }
    }
    while (top != -1)
        postfix[j++] = pop();
    postfix[j] = '\0';
}

// Stack for TAC generation
char tacStack[MAX][MAX];
int tacTop = -1;

void tacPush(char *str) {
    strcpy(tacStack[++tacTop], str);
}

char* tacPop() {
    return tacStack[tacTop--];
}

// Generate TAC from postfix
void generateTAC(char *postfix) {
    printf("\nThree-Address Code:\n");
    for (int i = 0; postfix[i]; i++) {
        char ch = postfix[i];

        if (isalnum(ch)) {
            char operand[2] = {ch, '\0'};
            tacPush(operand);
        } else {
            char op2[MAX], op1[MAX], result[MAX];
            strcpy(op2, tacPop());
            strcpy(op1, tacPop());

            sprintf(result, "t%d", tempCount++);
            printf("%s = %s %c %s\n", result, op1, ch, op2);
            tacPush(result);
        }
    }
}

int main() {
    char infix[MAX];

    printf("Enter an arithmetic expression (e.g., a+b*c): ");
    scanf("%s", infix);

    infixToPostfix(infix);
    printf("\nPostfix Expression: %s\n", postfix);

    generateTAC(postfix);

    return 0;
}
