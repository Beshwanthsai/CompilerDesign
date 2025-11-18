#include <stdio.h>
#include <string.h>

#define MAX 50

typedef struct {
    char var[10];
    char expr[50];
} Statement;

Statement code[MAX];
int n;

void copyPropagation() {
    printf("\n--- Applying Copy Propagation ---\n");
    
    for (int i = 0; i < n; i++) {

        char copyVar[10];
        if (sscanf(code[i].expr, "%s", copyVar) == 1 && 
            strlen(code[i].expr) < 10 && 
            !strchr(code[i].expr, '+') && 
            !strchr(code[i].expr, '-') && 
            !strchr(code[i].expr, '*') && 
            !strchr(code[i].expr, '/')) {
            

            printf("Found copy: %s = %s\n", code[i].var, copyVar);
            

            for (int j = i + 1; j < n; j++) {
                char temp[50], newExpr[50] = "";
                char *token;
                int replaced = 0;
                
                strcpy(temp, code[j].expr);
                token = strtok(temp, " ");
                
                while (token != NULL) {
                    if (strcmp(token, code[i].var) == 0) {
                        strcat(newExpr, copyVar);
                        replaced = 1;
                    } else {
                        strcat(newExpr, token);
                    }
                    strcat(newExpr, " ");
                    token = strtok(NULL, " ");
                }
                
                if (replaced) {
                    newExpr[strlen(newExpr) - 1] = '\0'; 
                    printf("Propagated: %s = %s -> %s = %s\n", 
                           code[j].var, code[j].expr, code[j].var, newExpr);
                    strcpy(code[j].expr, newExpr);
                }
            }
        }
    }
}

int main() {
    int choice;
    FILE *fp;
    
    printf("=== Copy Propagation Optimization ===\n");
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
        n = 5;
        strcpy(code[0].var, "a");
        strcpy(code[0].expr, "10");
        strcpy(code[1].var, "b");
        strcpy(code[1].expr, "a");
        strcpy(code[2].var, "c");
        strcpy(code[2].expr, "b + 5");
        strcpy(code[3].var, "d");
        strcpy(code[3].expr, "b * 2");
        strcpy(code[4].var, "e");
        strcpy(code[4].expr, "b - 3");
    }
    
    printf("\n--- Before Optimization ---\n");
    for (int i = 0; i < n; i++) {
        printf("%s = %s\n", code[i].var, code[i].expr);
    }
    
    copyPropagation();
    
    printf("\n--- After Optimization ---\n");
    for (int i = 0; i < n; i++) {
        printf("%s = %s\n", code[i].var, code[i].expr);
    }
    
    return 0;
}
