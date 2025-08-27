#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
#include "ast.h"

extern struct ASTNode* root;  /* solo declaramos */

int yyparse(void);
extern FILE* yyin;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s <archivo_entrada>\n", argv[0]);
        return 1;
    }

    FILE* f = fopen(argv[1], "r");
    if (!f) {
        perror("Error al abrir archivo");
        return 1;
    }

    yyin = f;

    if (yyparse() == 0) {
        printf("Parseo exitoso!\n\nÁrbol sintáctico:\n");
        ast_print(root, 0);
    } else {
        printf("Hubo errores de sintaxis.\n");
    }

    fclose(f);
    return 0;
}
