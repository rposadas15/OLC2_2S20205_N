%{
#include "parser.tab.h"
#include <string.h>
#include <stdlib.h>
%}

%%

[ \t\r\n]+          ;
"var"               { return VAR; }
"fmt.Println"       { return PRINT; }
"if"                { return IF; }
"then"              { return THEN; }
"end"               { return END; }
"int"               { return TINT; }
"float64"           { return TFLOAT; }
"string"            { return TSTRING; }
"bool"              { return TBOOL; }
"rune"              { return TRUNE; }
"&&"                { return AND; }
"||"                { return OR; }
"!"                 { return NOT; }
"=="                { return EQ; }
"!="                { return NEQ; }
">="                { return GEQ; }
">"                 { return GT; }
"<="                { return LEQ; }
"<"                 { return LT; }
":="                { return DOSPUNTOS_IGUAL; }
"="                 { return IGUAL; }
"("                 { return PARENTESIS_ABRE; }
")"                 { return PARENTESIS_CIERRA; }

[0-9]+"."[0-9]+     { yylval.str = strdup(yytext); return DECIMAL; }
[0-9]+              { yylval.str = strdup(yytext); return INT; }
\"([^"\n])*\"       { yylval.str = strdup(yytext); return CADENA; }
\'[^\']\'           { yylval.str = strdup(yytext); return CARACTER; }
"true"|"false"      { yylval.str = strdup(yytext); return BOOL; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.str = strdup(yytext); return PALABRA; }

.                   { /* ignorar desconocidos */ }

%%

int yywrap() { return 1; }
