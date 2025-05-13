#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Tree node structure
typedef struct Node {
    char data;
    struct Node *left, *right;
} Node;

Node *stack[MAX];
int top = -1;

void push(Node *node) {
    stack[++top] = node;
}

Node *pop() {
    return stack[top--];
}

Node *createNode(char data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Precedence for operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Infix to postfix conversion
void infixToPostfix(char infix[], char postfix[]) {
    char stack[MAX];
    int top = -1, j = 0;
    for (int i = 0; infix[i]; i++) {
        char token = infix[i];
        if (token == ' ') continue;

        if (isalnum(token)) {
            postfix[j++] = token;
        } else if (token == '(') {
            stack[++top] = token;
        } else if (token == ')') {
            while (top >= 0 && stack[top] != '(')
                postfix[j++] = stack[top--];
            top--; // Remove '('
        } else {
            while (top >= 0 && precedence(stack[top]) >= precedence(token))
                postfix[j++] = stack[top--];
            stack[++top] = token;
        }
    }
    while (top >= 0)
        postfix[j++] = stack[top--];
    postfix[j] = '\0';
}

// Build syntax tree from postfix
Node *buildTree(char postfix[]) {
    for (int i = 0; postfix[i]; i++) {
        char ch = postfix[i];
        Node *node = createNode(ch);

        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            node->right = pop();
            node->left = pop();
        }

        push(node);
    }
    return pop();
}

// Print the tree in rotated 2D format
void printTree(Node *root, int space) {
    if (root == NULL) return;

    space += 5;

    printTree(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++) printf(" ");
    printf("%c\n", root->data);

    printTree(root->left, space);
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter an infix expression (e.g., a+b*c): ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("\nPostfix: %s\n", postfix);

    Node *root = buildTree(postfix);

    printf("\nSyntax Tree (rotated 90 degrees):\n");
    printTree(root, 0);

    return 0;
}
