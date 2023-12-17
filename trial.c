#include <stdio.h>
#include <string.h>

typedef struct {
    char op[10];
    char arg1[10];
    char arg2[10];
    char result[10];
} ThreeAddressCode;

void generateAssembly(ThreeAddressCode *code, int numInstructions) {
    printf(".model small\n");
    printf(".data\n");

    for (int i = 0; i < numInstructions; i++) {
        printf("    %s DW ?\n", code[i].result);
    }

    printf(".code\n");

    printf("main PROC\n");

    for (int i = 0; i < numInstructions; i++) {
        if (strcmp(code[i].op, "MOV") == 0) {
            printf("    MOV %s, %s\n", code[i].result, code[i].arg1);
        } else if (strcmp(code[i].op, "ADD") == 0) {
            printf("    ADD %s, %s\n", code[i].result, code[i].arg1);
        } else if (strcmp(code[i].op, "SUB") == 0) {
            printf("    SUB %s, %s\n", code[i].result, code[i].arg1);
        }
    }

    printf("    MOV AH, 4CH\n");
    printf("    INT 21H\n");

    printf("main ENDP\n");
    printf("END main\n");
}

int main() {
    int numInstructions;
    printf("Enter the number of three-address code instructions: ");
    scanf("%d", &numInstructions);

    ThreeAddressCode code[numInstructions];

    printf("Enter three-address code instructions:\n");

    for (int i = 0; i < numInstructions; i++) {
        printf("Instruction %d: ", i + 1);
        scanf("%s %s %s %s", code[i].op, code[i].arg1, code[i].arg2, code[i].result);
    }

    generateAssembly(code, numInstructions);

    return 0;
}
