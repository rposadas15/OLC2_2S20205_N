#include <stdio.h>

extern int yyparse();

int main() {
    while (1) {
        printf("Iniciando el parser...\n");
        int resultado = yyparse();
        if (resultado == 0) {
            printf("Parseo completado exitosamente.\n");
        } else {
            printf("Error en el parseo.\n");
        }
    }
    return 0;
}