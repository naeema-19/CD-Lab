#include<stdio.h>
#include<string.h>

#define MAX_STATES 20
#define MAX_TRANSITIONS 100

char states[MAX_STATES][3];
char terms[MAX_STATES];
char table[MAX_STATES][MAX_STATES][MAX_STATES];

int n, m; // Number of states and terminals

void epsilonClosure(int state, char* closure) {
    strcpy(closure, "");
    strcat(closure, states[state]);

    for (int i = 0; i < n; i++) {
        if (strchr(table[state][m], states[i][0]) && strchr(closure, states[i][0]) == NULL) {
            strcat(closure, states[i]);
            epsilonClosure(i, closure);
        }
    }
}

void convertToNFAWithoutEpsilon() {
    printf("\nConverting NFA with ε transition to NFA without ε transition...\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (strlen(table[i][j]) > 1 && strchr(table[i][m], 'e')) {
                char closure[50];
                epsilonClosure(i, closure);

                for (int k = 0; k < strlen(closure); k++) {
                    for (int l = 0; l < m; l++) {
                        strcat(table[i][l], table[closure[k] - 'A'][l]);
                    }
                }

                table[i][m][0] = '\0'; // Remove ε transition
            }
        }
    }
}

void displayNFA() {
    printf("\nNFA without ε transition:\n");

    for (int i = 0; i < n; i++) {
        printf("\nState %c:\n", states[i][0]);
        for (int j = 0; j <= m; j++) {
            printf("  %c: %s\n", terms[j], table[i][j]);
        }
    }
}

int main() {
    printf("Enter the number of states: ");
    scanf("%d", &n);

    printf("Enter the number of terminals: ");
    scanf("%d", &m);

    printf("Enter the states:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", states[i]);
    }

    printf("Enter the terminals (excluding 'e'):\n");
    scanf("%s", terms);

    printf("Enter the transition table (use 'e' for ε transition):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            scanf("%s", table[i][j]);
        }
    }

    convertToNFAWithoutEpsilon();
    displayNFA();

    return 0;
}
