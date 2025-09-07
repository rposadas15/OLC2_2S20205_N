#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
#include "ast.h"
#include "sema.h"      // <--- NUEVO

extern struct ASTNode* root;
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

        // Política: 0 = prohibir shadowing; 1 = permitir shadowing
        set_shadowing_policy(0);

        int errs = check_semantics(root);
        if (errs == 0) {
            printf("\nChequeo semántico: OK (sin errores)\n");
        } else {
            printf("\nChequeo semántico: %d error(es)\n", errs);
        }
    } else {
        printf("Hubo errores de sintaxis.\n");
    }

    fclose(f);
    return 0;
}
