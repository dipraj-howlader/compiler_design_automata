#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 10
#define MAX 20

char prod[SIZE][MAX];
char first[SIZE][MAX], follow[SIZE][MAX];
int n;

void add(char *result, char c) {
    if (!strchr(result, c)) {
        int len = strlen(result);
        result[len] = c;
        result[len + 1] = '\0';
    }
}

void calcFirst(char symbol, char *res) {
    for (int i = 0; i < n; i++) {
        if (prod[i][0] == symbol) {
            if (!isupper(prod[i][2])) {
                add(res, prod[i][2]);
            } else {
                char temp[MAX] = "";
                calcFirst(prod[i][2], temp);
                for (int j = 0; j < strlen(temp); j++) {
                    add(res, temp[j]);
                }
            }
        }
    }
}

void calcFollow(char symbol, char *res, char start) {
    if (symbol == start) add(res, '$');

    for (int i = 0; i < n; i++) {
        int len = strlen(prod[i]);
        for (int j = 2; j < len; j++) {
            if (prod[i][j] == symbol) {
                if (j + 1 < len) {
                    if (!isupper(prod[i][j + 1])) {
                        add(res, prod[i][j + 1]);
                    } else {
                        char temp[MAX] = "";
                        calcFirst(prod[i][j + 1], temp);
                        for (int k = 0; k < strlen(temp); k++) {
                            if (temp[k] != '#') add(res, temp[k]);
                        }

                        // If ε in FIRST(next), also add FOLLOW(lhs)
                        if (strchr(temp, '#')) {
                            char tempFollow[MAX] = "";
                            calcFollow(prod[i][0], tempFollow, start);
                            for (int k = 0; k < strlen(tempFollow); k++) {
                                add(res, tempFollow[k]);
                            }
                        }
                    }
                } else if (prod[i][0] != symbol) {
                    // Symbol at end — add FOLLOW(lhs)
                    char tempFollow[MAX] = "";
                    calcFollow(prod[i][0], tempFollow, start);
                    for (int k = 0; k < strlen(tempFollow); k++) {
                        add(res, tempFollow[k]);
                    }
                }
            }
        }
    }
}

int isDone(char symbol, char done[], int count) {
    for (int i = 0; i < count; i++) {
        if (done[i] == symbol)
            return 1;
    }
    return 0;
}

int main() {
    char done[SIZE];
    int doneCount = 0;

    printf("Enter number of productions: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        printf("Enter production %d (e.g., E=TX): ", i + 1);
        scanf("%s", prod[i]);
    }

    printf("\nFIRST sets:\n");
    for (int i = 0; i < n; i++) {
        char lhs = prod[i][0];
        if (!isDone(lhs, done, doneCount)) {
            char res[MAX] = "";
            calcFirst(lhs, res);
            printf("FIRST(%c) = { ", lhs);
            for (int j = 0; j < strlen(res); j++)
                printf("%c ", res[j]);
            printf("}\n");

            done[doneCount++] = lhs;
        }
    }

    doneCount = 0;
    printf("\nEnter start symbol for FOLLOW: ");
    char start;
    scanf(" %c", &start);

    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < n; i++) {
        char lhs = prod[i][0];
        if (!isDone(lhs, done, doneCount)) {
            char res[MAX] = "";
            calcFollow(lhs, res, start);
            printf("FOLLOW(%c) = { ", lhs);
            for (int j = 0; j < strlen(res); j++)
                printf("%c ", res[j]);
            printf("}\n");

            done[doneCount++] = lhs;
        }
    }

    return 0;
}



/* 
Enter number of productions: 4

E=TX
X=+TX
X=#
T=FY
Y=*FY
Y=#
F=(E)
F=i
Enter start symbol for FOLLOW set: E

*/