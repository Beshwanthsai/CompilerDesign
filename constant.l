#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char input[20];
int i = 0;
void E(), T(), Eprime();
void E() { T(); Eprime(); }
void Eprime() {
if (input[i] == '+') {
i++;
T();
Eprime();
void T() {
if (input[i] == 'i' && input[i+1] == 'd')
i += 2;
else {
printf("Error\n");
exit(0);
}
}
int main() {
printf("Enter expression: ");
scanf("%s", input);
E();
if (input[i] == '\0')
printf("Accepted\n");
else
printf("Rejected\n");
}

