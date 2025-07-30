%{
#include "parser.tab.h"
%}

%%

[0-9]+      { yylval.entero = atoi(yytext); return INT; }
[ \t]       ; // Ignorar espacios y tabulaciones
\n          return '\n';
.           return yytext[0];

%%

int yywrap() {
    return 1;
}
