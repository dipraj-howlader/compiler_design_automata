#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Match 'a'
bool match_a(const char *str) {
    return (strlen(str) == 1 && str[0] == 'a');
}

// Match 'abb'
bool match_abb(const char *str) {
    return (strcmp(str, "abb") == 0);
}

// Match 'a*b+'
bool match_a_star_b_plus(const char *str) {
    int i = 0;

    // Count a's
    while (str[i] == 'a') {
        i++;
    }

    // Must have at least one 'b'
    if (str[i] != 'b') {
        return false;
    }

    // At least one b required
    int b_count = 0;
    while (str[i] == 'b') {
        i++;
        b_count++;
    }

    // If b_count >= 1 and no other characters, it's a match
    return (b_count >= 1 && str[i] == '\0');
}

int main() {
    char input[100];

    printf("Enter a string: ");
    scanf("%s", input);

    if (match_abb(input)) {
        printf("Matched: 'abb'\n");
    }
    else if (match_a(input)) {
        printf("Matched: 'a'\n");
    }
    else if (match_a_star_b_plus(input)) {
        printf("Matched: 'a*b+'\n");
    }
    else {
        printf("No match found.\n");
    }

    return 0;
}
