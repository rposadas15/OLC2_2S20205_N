#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Symbol {
    char *name;           // identificador
    char *type;           // nombre del tipo (e.g., "int", "float64", "string")
    struct Symbol *next;  // lista enlazada simple dentro del entorno
} Symbol;

typedef struct Env {
    Symbol *table;        // tabla (lista) de símbolos declarados en este entorno
    struct Env *parent;   // entorno padre (externo)
} Env;

/* Crea un nuevo entorno cuyo padre es 'parent' */
Env* env_push(Env *parent);

/* Destruye el entorno actual y devuelve el padre (para facilitar pop) */
Env* env_pop(Env *env);

/* Busca un símbolo por nombre empezando en 'env' y siguiendo hacia los padres */
Symbol* env_lookup(Env *env, const char *name);

/* Busca solo en el entorno actual (sin mirar a los padres) */
Symbol* env_lookup_here(Env *env, const char *name);

/* 
 * Declara un símbolo en el entorno actual.
 * - si allow_shadowing = 0, prohíbe declarar una variable que ya exista en algún entorno padre.
 * - si allow_shadowing = 1, solo prohíbe redeclarar en el entorno actual.
 * Devuelve:
 *   0 = ok
 *   1 = ya existe en el entorno actual
 *   2 = existe en un padre y shadowing no permitido
 */
int env_declare(Env *env, const char *name, const char *type, int allow_shadowing);

/* Libera completamente una cadena de entornos (útil al final) */
void env_free_chain(Env *env);

/* Utilitario: imprime el stack de entornos (para debug) */
void env_debug_dump(Env *env);

#ifdef __cplusplus
}
#endif

#endif
