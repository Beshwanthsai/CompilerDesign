%{
    #include<stdio.h>
    int yywrap(void);
%}
%%
[0-9]+ {printf("These are constants: %s\n", yytext);}
[a-z A-Z]+ {printf("These are not constants: %s\n", yytext);}
.|\n;
%%

int yywrap(void) {
    return 1;
}

int main()
{
    yylex();
    return 0;
}


