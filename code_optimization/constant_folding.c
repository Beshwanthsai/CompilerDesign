#include <stdio.h>
#include <string.h>

#define MAX 50

typedef struct {
    char var[10];
    char expr[50];
} Statement;

Statement code[MAX];
int n;

void constantFolding() {
    printf("\n--- Applying Constant Folding ---\n");
    
    for (int i = 0; i < n; i++) {
        int a, b;
        char op, temp[50];
        

        if (sscanf(code[i].expr, "%d %c %d", &a, &op, &b) == 3) {
            int result;
            
            switch(op) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': 
                    if (b != 0) result = a / b;
                    else { printf("Error: Division by zero\n"); continue; }
                    break;
                default: continue;
            }
            
            printf("Folded: %s = %d %c %d -> %s = %d\n", 
                   code[i].var, a, op, b, code[i].var, result);
            sprintf(code[i].expr, "%d", result);
        }
    }
}

int main() {
    int choice;
    FILE *fp;
    
    printf("=== Constant Folding Optimization ===\n");
    printf("\n1. Read from file\n2. Example\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        char filename[100];
        printf("Enter filename: ");
        scanf("%s", filename);
        
        fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("Error: Could not open file %s\n", filename);
            return 1;
        }
        
        n = 0;

        while (fscanf(fp, "%s = %[^\n]", code[n].var, code[n].expr) == 2) {
            n++;
            if (n >= MAX) break;
        }
        
        fclose(fp);
        
        if (n == 0) {
            printf("Error: No statements found in file\n");
            return 1;
        }
    } else {
        n = 4;
        strcpy(code[0].var, "a");
        strcpy(code[0].expr, "5 + 3");
        strcpy(code[1].var, "b");
        strcpy(code[1].expr, "10 * 2");
        strcpy(code[2].var, "c");
        strcpy(code[2].expr, "20 / 4");
        strcpy(code[3].var, "d");
        strcpy(code[3].expr, "15 - 7");
    }
    
    printf("\n--- Before Optimization ---\n");
    for (int i = 0; i < n; i++) {
        printf("%s = %s\n", code[i].var, code[i].expr);
    }
    
    constantFolding();
    
    printf("\n--- After Optimization ---\n");
    for (int i = 0; i < n; i++) {
        printf("%s = %s\n", code[i].var, code[i].expr);
    }
    
    return 0;
}
