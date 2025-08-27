%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

struct ASTNode* root = NULL;

int yylex(void);
void yyerror(const char *s);
%}

%union {
    char* str;
    struct ASTNode* node;
}

/* === TOKENS === */
%token VAR PRINT IF THEN END
%token TINT TFLOAT TSTRING TBOOL TRUNE
%token DOSPUNTOS_IGUAL IGUAL
%token PARENTESIS_ABRE PARENTESIS_CIERRA
%token AND OR NOT
%token EQ NEQ GEQ GT LEQ LT

%token <str> INT DECIMAL CARACTER CADENA PALABRA BOOL

/* === TIPOS DE RETORNO === */
%type <node> inicio listainstrucciones instruccion
%type <node> print variables asignacion instruccion_if
%type <node> tipo expr

%%

inicio: listainstrucciones        { root = $1; }
      ;

listainstrucciones: instruccion                 { $$ = $1; }
                  | listainstrucciones instruccion { $$ = ast_link($1, $2); }
                  ;

instruccion: print
           | variables
           | asignacion
           | instruccion_if
           ;

print: PRINT PARENTESIS_ABRE expr PARENTESIS_CIERRA
        { $$ = ast_print_stmt($3); }
     ;

variables: VAR PALABRA tipo
             { $$ = ast_var_decl($2, $3, NULL); }
         | VAR PALABRA tipo IGUAL expr
             { $$ = ast_var_decl($2, $3, $5); }
         ;

asignacion: PALABRA IGUAL expr
              { $$ = ast_assign($1, $3); }
          | PALABRA DOSPUNTOS_IGUAL expr
              { $$ = ast_assign($1, $3); }
          ;

tipo: TINT      { $$ = ast_type("int"); }
    | TFLOAT    { $$ = ast_type("float64"); }
    | TSTRING   { $$ = ast_type("string"); }
    | TBOOL     { $$ = ast_type("bool"); }
    | TRUNE     { $$ = ast_type("rune"); }
    ;

instruccion_if: IF PARENTESIS_ABRE expr PARENTESIS_CIERRA THEN listainstrucciones END IF
                 { $$ = ast_if($3, $6); }
              ;

/* === EXPRESIONES === */
expr: PARENTESIS_ABRE expr PARENTESIS_CIERRA   { $$ = $2; }
    | INT        { $$ = ast_literal($1); }
    | DECIMAL    { $$ = ast_literal($1); }
    | CARACTER   { $$ = ast_literal($1); }
    | CADENA     { $$ = ast_literal($1); }
    | BOOL       { $$ = ast_literal($1); }
    | PALABRA    { $$ = ast_identifier($1); }

    | expr '*' expr  { $$ = ast_binop("*", $1, $3); }
    | expr '/' expr  { $$ = ast_binop("/", $1, $3); }
    | expr '+' expr  { $$ = ast_binop("+", $1, $3); }
    | expr '-' expr  { $$ = ast_binop("-", $1, $3); }

    | expr AND expr  { $$ = ast_binop("&&", $1, $3); }
    | expr OR expr   { $$ = ast_binop("||", $1, $3); }
    | NOT expr       { $$ = ast_unop("!", $2); }

    | expr EQ expr   { $$ = ast_binop("==", $1, $3); }
    | expr NEQ expr  { $$ = ast_binop("!=", $1, $3); }
    | expr GEQ expr  { $$ = ast_binop(">=", $1, $3); }
    | expr GT expr   { $$ = ast_binop(">", $1, $3); }
    | expr LEQ expr  { $$ = ast_binop("<=", $1, $3); }
    | expr LT expr   { $$ = ast_binop("<", $1, $3); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error de sintaxis: %s\n", s);
}
