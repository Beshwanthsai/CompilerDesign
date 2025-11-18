#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

typedef struct {
    char var[10];
    char expr[50];
} Statement;

Statement code[MAX];
int n;

int isPowerOf2(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

int log2_int(int n) {
    int count = 0;
    while (n > 1) {
        n = n >> 1;
        count++;
    }
    return count;
}

void strengthReduction() {
    printf("\n--- Applying Strength Reduction ---\n");
    
    for (int i = 0; i < n; i++) {
        char var1[10], op, var2[10];
        int num;
        

        if (sscanf(code[i].expr, "%s %c %d", var1, &op, &num) == 3) {
            

            if (op == '*' && isPowerOf2(num)) {
                int shift = log2_int(num);
                printf("Reduced: %s = %s * %d -> %s = %s << %d\n", 
                       code[i].var, var1, num, code[i].var, var1, shift);
                sprintf(code[i].expr, "%s << %d", var1, shift);
            }

            else if (op == '/' && isPowerOf2(num)) {
                int shift = log2_int(num);
                printf("Reduced: %s = %s / %d -> %s = %s >> %d\n", 
                       code[i].var, var1, num, code[i].var, var1, shift);
                sprintf(code[i].expr, "%s >> %d", var1, shift);
            }

            else if (op == '*' && num == 0) {
                printf("Reduced: %s = %s * 0 -> %s = 0\n", 
                       code[i].var, var1, code[i].var);
                strcpy(code[i].expr, "0");
            }

            else if (op == '*' && num == 1) {
                printf("Reduced: %s = %s * 1 -> %s = %s\n", 
                       code[i].var, var1, code[i].var, var1);
                strcpy(code[i].expr, var1);
            }

            else if (op == '+' && num == 0) {
                printf("Reduced: %s = %s + 0 -> %s = %s\n", 
                       code[i].var, var1, code[i].var, var1);
                strcpy(code[i].expr, var1);
            }

            else if (op == '-' && num == 0) {
                printf("Reduced: %s = %s - 0 -> %s = %s\n", 
                       code[i].var, var1, code[i].var, var1);
                strcpy(code[i].expr, var1);
            }
        }
    }
}

int main() {
    int choice;
    FILE *fp;
    
    printf("=== Strength Reduction Optimization ===\n");
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
        // Read each line from file
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
        n = 6;
        strcpy(code[0].var, "a");
        strcpy(code[0].expr, "x * 2");
        strcpy(code[1].var, "b");
        strcpy(code[1].expr, "y * 4");
        strcpy(code[2].var, "c");
        strcpy(code[2].expr, "z / 8");
        strcpy(code[3].var, "d");
        strcpy(code[3].expr, "p * 0");
        strcpy(code[4].var, "e");
        strcpy(code[4].expr, "q * 1");
        strcpy(code[5].var, "f");
        strcpy(code[5].expr, "r + 0");
    }
    
    printf("\n--- Before Optimization ---\n");
    for (int i = 0; i < n; i++) {
        printf("%s = %s\n", code[i].var, code[i].expr);
    }
    
    strengthReduction();
    
    printf("\n--- After Optimization ---\n");
    for (int i = 0; i < n; i++) {
        printf("%s = %s\n", code[i].var, code[i].expr);
    }
    
    printf("\nNote: << is left shift, >> is right shift (faster than multiply/divide)\n");
    
    return 0;
}
