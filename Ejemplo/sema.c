#include "sema.h"
#include "symbols.h"
#include <stdio.h>
#include <string.h>

static int g_errors = 0;
static int g_allow_shadowing = 0;

void set_shadowing_policy(int allow_shadowing) {
    g_allow_shadowing = allow_shadowing ? 1 : 0;
}

static void error(const char *msg, const char *name) {
    ++g_errors;
    if (name) fprintf(stderr, "[Semántica] %s: %s\n", msg, name);
    else      fprintf(stderr, "[Semántica] %s\n", msg);
}

/* Dado un nodo "type", devuelve su nombre */
static const char* type_name(struct ASTNode *typeNode) {
    if (!typeNode) return "";
    if (typeNode->kind && strcmp(typeNode->kind, "type") == 0) {
        return typeNode->value ? typeNode->value : "";
    }
    return "";
}

static void visit(struct ASTNode *n, Env **envp);

static void visit_expr(struct ASTNode *n, Env **envp) {
    if (!n) return;
    if (strcmp(n->kind, "id") == 0) {
        if (!env_lookup(*envp, n->value)) {
            error("Uso de variable no declarada", n->value);
        }
        return;
    }
    // recorre hijos por defecto
    visit(n->left, envp);
    visit(n->right, envp);
}

static void visit(struct ASTNode *n, Env **envp) {
    if (!n) return;

    if (strcmp(n->kind, "link") == 0) {
        visit(n->left, envp);
        visit(n->right, envp);
        return;
    }

    if (strcmp(n->kind, "var") == 0) {
        const char *name = n->value;          // id
        const char *ty   = type_name(n->left);// tipo viene en left
        int rc = env_declare(*envp, name, ty, g_allow_shadowing);
        if (rc == 1) {
            error("Redeclaración en el mismo entorno", name);
        } else if (rc == 2) {
            error("Redeclaración en entorno interno (shadowing prohibido)", name);
        }
        // si hay inicialización en right, validarla
        visit_expr(n->right, envp);
        return;
    }

    if (strcmp(n->kind, "assign") == 0) {
        const char *name = n->value;
        if (!env_lookup(*envp, name)) {
            error("Asignación a variable no declarada", name);
        }
        visit_expr(n->left, envp);  // en 'assign', left guarda la expr (según ast.c)
        return;
    }

    if (strcmp(n->kind, "print") == 0) {
        visit_expr(n->left, envp);
        return;
    }

    if (strcmp(n->kind, "if") == 0) {
        // cond en left, cuerpo en right
        visit_expr(n->left, envp);
        // nuevo entorno para el cuerpo
        *envp = env_push(*envp);
        visit(n->right, envp);
        *envp = env_pop(*envp);
        return;
    }

    // binop, unop, literal, type, etc.
    visit(n->left, envp);
    visit(n->right, envp);
}

int check_semantics(struct ASTNode *root) {
    g_errors = 0;
    Env *env = env_push(NULL);  // global
    visit(root, &env);
    env_free_chain(env);
    return g_errors;
}
