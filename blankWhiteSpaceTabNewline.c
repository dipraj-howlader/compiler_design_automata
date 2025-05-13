#include <stdio.h>
#include <string.h>

int main() {
    char line[1000];
    int blanks = 0, tabs = 0, newlines = 0, others = 0;

    printf("Enter text line by line (type END to stop):\n");

    while (1) {
        fgets(line, sizeof(line), stdin);

        if (strncmp(line, "END", 3) == 0)
            break;

        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == ' ')
                blanks++;
            else if (line[i] == '\t')
                tabs++;
            else if (line[i] == '\n')
                newlines++;
            else
                others++;
        }
    }

    printf("\n--- Character Count ---\n");
    printf("Blanks   : %d\n", blanks);
    printf("Tabs     : %d\n", tabs);
    printf("Newlines : %d\n", newlines);
    printf("Others   : %d\n", others);

    return 0;
}


/*
Hello    World!
This	is a test.
END

*/