#include <stdio.h>
#include <ctype.h>
#include <string.h>

char stack[100];
int top = -1;
int tempCount = 1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int precedence(char c) {
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}


void infixToPostfix(char infix[], char postfix[]) {
    int i, k = 0;
    for (i = 0; i < (int)strlen(infix); i++) {
        char c = infix[i];

        if (isalnum((unsigned char)c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[k++] = pop();
            if (top != -1) pop();
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (top != -1 && precedence(stack[top]) >= precedence(c))
                postfix[k++] = pop();
            push(c);
        }
    }
    while (top != -1)
        postfix[k++] = pop();
    postfix[k] = '\0';
}


void generate3AC(char postfix[], char lhs) {
    char tempStack[100];
    int tTop = -1;
    int localTempCount = tempCount;

    printf("\n--- Three Address Code ---\n");
    for (int i = 0; i < (int)strlen(postfix); i++) {
        char c = postfix[i];

        if (isalnum((unsigned char)c)) {
            tempStack[++tTop] = c;
        } else {
            char op2 = tempStack[tTop--];
            char op1 = tempStack[tTop--];
            printf("t%d = %c %c %c\n", localTempCount, op1, c, op2);
            tempStack[++tTop] = 'A' + (localTempCount - 1); 
            localTempCount++;
        }
    }

    if (localTempCount > 1)
        printf("%c = t%d\n", lhs, localTempCount - 1);
    else
        printf("%c = %c\n", lhs, tempStack[tTop]); 
}

void generateQuadruple(char postfix[], char lhs) {
    char tempStack[100];
    int tTop = -1;
    int localTempCount = tempCount;

    printf("\n--- Quadruple Representation ---\n");
    printf("Operator\tArg1\tArg2\tResult\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < (int)strlen(postfix); i++) {
        char c = postfix[i];

        if (isalnum((unsigned char)c)) {
            tempStack[++tTop] = c;
        } else {
            char op2 = tempStack[tTop--];
            char op1 = tempStack[tTop--];
            printf("%c\t\t%c\t%c\tt%d\n", c, op1, op2, localTempCount);
            tempStack[++tTop] = 'A' + (localTempCount - 1); 
            localTempCount++;
        }
    }

    if (localTempCount > 1)
        printf("=\t\tt%d\t-\t%c\n", localTempCount - 1, lhs);
    else
        printf("=\t\t%c\t-\t%c\n", tempStack[tTop], lhs);
}

int main() {
    char expr[200], lhs, rhs[200], postfix[200];

    printf("Enter expression (e.g. a=b*c+d): ");
    if (scanf("%199s", expr) != 1) return 0;

    lhs = expr[0];


    int j = 0;
    for (int i = 2; i < (int)strlen(expr); i++) {
        rhs[j++] = expr[i];
    }
    rhs[j] = '\0';


    top = -1;
    tempCount = 1;

    infixToPostfix(rhs, postfix);
    printf("\nPostfix: %s\n", postfix);
    
    generate3AC(postfix, lhs);
    generateQuadruple(postfix, lhs);

    return 0;
}