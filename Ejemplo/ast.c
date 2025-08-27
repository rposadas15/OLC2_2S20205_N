#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct ASTNode* make_node(const char* kind, const char* value, struct ASTNode* left, struct ASTNode* right) {
    struct ASTNode* n = malloc(sizeof(struct ASTNode));
    n->kind = strdup(kind);
    n->value = value ? strdup(value) : NULL;
    n->left = left;
    n->right = right;
    return n;
}

struct ASTNode* ast_link(struct ASTNode* left, struct ASTNode* right) { return make_node("link", NULL, left, right); }
struct ASTNode* ast_print_stmt(struct ASTNode* expr) { return make_node("print", NULL, expr, NULL); }
struct ASTNode* ast_var_decl(char* id, struct ASTNode* type, struct ASTNode* expr) { return make_node("var", id, type, expr); }
struct ASTNode* ast_assign(char* id, struct ASTNode* expr) { return make_node("assign", id, expr, NULL); }
struct ASTNode* ast_type(char* typeName) { return make_node("type", typeName, NULL, NULL); }
struct ASTNode* ast_if(struct ASTNode* cond, struct ASTNode* body) { return make_node("if", NULL, cond, body); }
struct ASTNode* ast_literal(char* value) { return make_node("literal", value, NULL, NULL); }
struct ASTNode* ast_identifier(char* name) { return make_node("id", name, NULL, NULL); }
struct ASTNode* ast_binop(char* op, struct ASTNode* left, struct ASTNode* right) { return make_node("binop", op, left, right); }
struct ASTNode* ast_unop(char* op, struct ASTNode* expr) { return make_node("unop", op, expr, NULL); }

void ast_print(struct ASTNode* node, int depth) {
    if (!node) return;
    for (int i=0; i<depth; i++) printf("  ");
    printf("%s", node->kind);
    if (node->value) printf(" (%s)", node->value);
    printf("\n");
    ast_print(node->left, depth+1);
    ast_print(node->right, depth+1);
}
