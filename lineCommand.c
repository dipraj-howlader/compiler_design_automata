#include <stdio.h>
#include <string.h>

int main() {
    char line[1000];

    printf("Enter a line of code: ");
    fgets(line, sizeof(line), stdin);  // Read line with spaces

    // Check for single-line comment
    if (line[0] == '/' && line[1] == '/') {
        printf("It is a single-line comment.\n");
    }
    // Check for multi-line comment
    else if (line[0] == '/' && line[1] == '*') {
        int len = strlen(line);
        // Check if it ends with */
        if (line[len - 3] == '*' && line[len - 2] == '/') {
            printf("It is a multi-line comment.\n");
        } else {
            printf("It is the start of a multi-line comment (not complete in one line).\n");
        }
    }
    else {
        printf("It is NOT a comment.\n");
    }

    return 0;
}



// input: /* comment */ //this is comment