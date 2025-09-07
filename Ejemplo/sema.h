#ifndef SEMA_H
#define SEMA_H

#include "ast.h"

/* Config de política: 0 = no permitir shadowing; 1 = permitir */
void set_shadowing_policy(int allow_shadowing);

/* Retorna el número de errores semánticos encontrados */
int check_semantics(struct ASTNode *root);

#endif
