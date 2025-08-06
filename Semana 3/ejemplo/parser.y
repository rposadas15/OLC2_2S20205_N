%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
void yyerror(const char *s);
%}

%union {
    int entero;
    char* cadena;
    char* id;
}

/* Tokens con tipo */
%token <entero> ENTERO
%token <cadena> CADENA
%token <id> ID

%token PRINTLN VAR IGUAL DOSPUNTOS_IGUAL PAR_ABRE PAR_CIERRA

/* Tokens para tipos */
%token TIPO_INT TIPO_FLOAT TIPO_STRING TIPO_BOOL TIPO_RUNE

%type <entero> expr tipo instruccion listainstrucciones

%%

inicio:
    listainstrucciones
    ;

listainstrucciones:
      listainstrucciones instruccion
    | instruccion
    ;

instruccion:
      PRINTLN PAR_ABRE expr PAR_CIERRA {
          printf("Print: %d\n", $3);
      }
    | VAR ID tipo {
          printf("Declaración de variable: %s tipo %d\n", $2, $3);
      }
    | VAR ID tipo IGUAL expr {
          printf("Declaración con asignación: %s = %d (tipo %d)\n", $2, $5, $3);
      }
    | ID IGUAL expr {
          printf("Asignación con = : %s = %d\n", $1, $3);
      }
    | ID DOSPUNTOS_IGUAL expr {
          printf("Asignación con := : %s := %d\n", $1, $3);
      }
    ;

tipo:
      TIPO_INT     { $$ = 1; }
    | TIPO_FLOAT   { $$ = 2; }
    | TIPO_STRING  { $$ = 3; }
    | TIPO_BOOL    { $$ = 4; }
    | TIPO_RUNE    { $$ = 5; }
    ;

expr:
      ENTERO         { $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
