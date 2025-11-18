#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[100];
int i = 0;

void E();
void Ep();
void T();

void T() {
    if (input[i]=='i' && input[i+1]=='d') {
        i += 2;   // consume "id"
    } else {
        printf("Invalid\n");
        exit(0);
    }
}

void Ep() {
    while (input[i] == '+') {
        i++;      // consume '+'
        T();      // read next id
    }
}

void E() {
    T();     // first id
    Ep();    // remaining +id +id...
}

int main() {
    scanf("%s", input);

    E();

    if (input[i] == '\0')
        printf("Valid\n");
    else
        printf("Invalid\n");

    return 0;
}