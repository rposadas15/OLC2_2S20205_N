%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(char *s);
%}

%union {
    int entero;
}

%token <entero> INT
%left '+' '-'
%left '*' '/'
%type <entero> expr

%start input

%%

input:
    /* vacío */
    | input line
    ;

line:
    expr '\n'   { printf("Resultado: %d\n", $1); }
    ;

expr:
    expr '+' expr   { $$ = $1 + $3; }
  | expr '-' expr   { $$ = $1 - $3; }
  | expr '*' expr   { $$ = $1 * $3; }
  | expr '/' expr   { 
        if ($3 == 0) {
            yyerror("Error: división entre cero.");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
    }
  | INT             { $$ = $1; }
  ;

%%

int main() {
    while (1) {
        printf("Ingrese una expresión: ");
        yyparse(); // Analiza una línea
    }
    return 0;
}

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
