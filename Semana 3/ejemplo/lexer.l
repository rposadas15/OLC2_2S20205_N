%{
#include "parser.tab.h"
#include <string.h>
#include <stdlib.h>
%}

%%

[ \t\r\n]+                     { /* ignorar espacios en blanco */ }

"var"                         { return VAR; }
"fmt.Println"                 { return PRINTLN; }

"int"                         { return TIPO_INT; }
"float64"                     { return TIPO_FLOAT; }
"string"                      { return TIPO_STRING; }
"bool"                        { return TIPO_BOOL; }
"rune"                        { return TIPO_RUNE; }

":="                          { return DOSPUNTOS_IGUAL; }
"="                           { return IGUAL; }
"("                           { return PAR_ABRE; }
")"                           { return PAR_CIERRA; }

"+"                           { return '+'; }
"-"                           { return '-'; }
"*"                           { return '*'; }
"/"                           { return '/'; }

[0-9]+                        { yylval.entero = atoi(yytext); return ENTERO; }

\"([^\"\r\n]|\"\")*\"         { yylval.cadena = strdup(yytext); return CADENA; }

[a-zA-Z_][a-zA-Z0-9_]*        { yylval.id = strdup(yytext); return ID; }

.                             { printf("Carácter no reconocido: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
