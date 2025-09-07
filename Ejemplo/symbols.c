#include "symbols.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char* str_dup(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s);
    char *r = (char*)malloc(n + 1);
    memcpy(r, s, n + 1);
    return r;
}

Env* env_push(Env *parent) {
    Env *e = (Env*)malloc(sizeof(Env));
    e->table = NULL;
    e->parent = parent;
    return e;
}

Env* env_pop(Env *env) {
    if (!env) return NULL;
    // libera símbolos del entorno actual
    Symbol *cur = env->table;
    while (cur) {
        Symbol *nx = cur->next;
        free(cur->name);
        free(cur->type);
        free(cur);
        cur = nx;
    }
    Env *p = env->parent;
    free(env);
    return p;
}

Symbol* env_lookup_here(Env *env, const char *name) {
    for (Symbol *s = env ? env->table : NULL; s; s = s->next) {
        if (strcmp(s->name, name) == 0) return s;
    }
    return NULL;
}

Symbol* env_lookup(Env *env, const char *name) {
    for (Env *e = env; e; e = e->parent) {
        Symbol *s = env_lookup_here(e, name);
        if (s) return s;
    }
    return NULL;
}

int env_declare(Env *env, const char *name, const char *type, int allow_shadowing) {
    if (!env) return 2; // sin entorno actual
    if (env_lookup_here(env, name)) return 1; // ya existe aquí
    if (!allow_shadowing && env_lookup(env->parent, name)) return 2; // existe en un padre

    Symbol *s = (Symbol*)malloc(sizeof(Symbol));
    s->name = str_dup(name);
    s->type = str_dup(type ? type : "");
    s->next = env->table;
    env->table = s;
    return 0;
}

void env_free_chain(Env *env) {
    while (env) env = env_pop(env);
}

void env_debug_dump(Env *env) {
    int level = 0;
    for (Env *e = env; e; e = e->parent, ++level) {
        fprintf(stderr, "== ENTORNO %d ==\n", level);
        for (Symbol *s = e->table; s; s = s->next) {
            fprintf(stderr, "  %s : %s\n", s->name, s->type);
        }
    }
}
