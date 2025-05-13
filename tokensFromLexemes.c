#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if", "int",
    "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile",
    "while"
};

bool isKeyword(const char *str) {
    int n = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return true;
    }
    return false;
}

bool isNumber(const char *str) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

bool isIdentifier(const char *str) {
    if (!(isalpha(str[0]) || str[0] == '_'))
        return false;
    for (int i = 1; str[i]; i++) {
        if (!(isalnum(str[i]) || str[i] == '_'))
            return false;
    }
    return true;
}

bool isOperator(const char *str) {
    const char *ops[] = {"+", "-", "*", "/", "=", "==", "<", "<=", ">", ">=", "!=", "&&", "||"};
    int n = sizeof(ops) / sizeof(ops[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(str, ops[i]) == 0)
            return true;
    }
    return false;
}

bool isSeparator(char ch) {
    return ch == ';' || ch == ',' || ch == '(' || ch == ')' || ch == '{' || ch == '}';
}

void recognizeTokens(const char *line) {
    char token[100];
    int i = 0, j = 0;
    while (line[i] != '\0') {
        // Skip whitespace
        if (isspace(line[i])) {
            i++;
            continue;
        }

        // Handle string literals
        if (line[i] == '"') {
            j = 0;
            token[j++] = line[i++];
            while (line[i] != '"' && line[i] != '\0') {
                token[j++] = line[i++];
            }
            if (line[i] == '"') token[j++] = line[i++];
            token[j] = '\0';
            printf("%s : String Literal\n", token);
            continue;
        }

        // Handle multi-character operators
        if (ispunct(line[i])) {
            if ((line[i] == '=' || line[i] == '!' || line[i] == '<' || line[i] == '>') && line[i+1] == '=') {
                printf("%c%c : Operator\n", line[i], line[i+1]);
                i += 2;
                continue;
            } else if (line[i] == '&' && line[i+1] == '&') {
                printf("&& : Operator\n");
                i += 2;
                continue;
            } else if (line[i] == '|' && line[i+1] == '|') {
                printf("|| : Operator\n");
                i += 2;
                continue;
            } else if (isSeparator(line[i])) {
                printf("%c : Separator\n", line[i]);
                i++;
                continue;
            } else {
                printf("%c : Operator\n", line[i]);
                i++;
                continue;
            }
        }

        // Handle identifiers, keywords, numbers
        j = 0;
        while (isalnum(line[i]) || line[i] == '_') {
            token[j++] = line[i++];
        }
        token[j] = '\0';

        if (strlen(token) > 0) {
            if (isKeyword(token))
                printf("%s : Keyword\n", token);
            else if (isNumber(token))
                printf("%s : Number\n", token);
            else
                printf("%s : Identifier\n", token);
        }
    }
}

int main() {
    char line[256];
    while(1){
    printf("Enter a line of code: ");
    fgets(line, sizeof(line), stdin);
    recognizeTokens(line);
    }
    return 0;
}


//for(i=0; i<10; i++) printf("Hi");
