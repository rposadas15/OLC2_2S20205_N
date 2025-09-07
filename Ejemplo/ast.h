#ifndef AST_H
#define AST_H

struct Loc {
    int first_line, first_column;
    int last_line,  last_column;
};

struct ASTNode {
    char* kind;
    char* value;
    struct ASTNode* left;
    struct ASTNode* right;
    struct Loc loc;
};

struct ASTNode* ast_link(struct ASTNode* left, struct ASTNode* right);
struct ASTNode* ast_print_stmt(struct ASTNode* expr);
struct ASTNode* ast_var_decl(char* id, struct ASTNode* type, struct ASTNode* expr);
struct ASTNode* ast_assign(char* id, struct ASTNode* expr);
struct ASTNode* ast_type(char* typeName);
struct ASTNode* ast_if(struct ASTNode* cond, struct ASTNode* body);
struct ASTNode* ast_literal(char* value);
struct ASTNode* ast_identifier(char* name);
struct ASTNode* ast_binop(char* op, struct ASTNode* left, struct ASTNode* right);
struct ASTNode* ast_unop(char* op, struct ASTNode* expr);
void ast_print(struct ASTNode* node, int depth);

static inline void ast_set_loc(struct ASTNode* n, int fl, int fc, int ll, int lc) {
    if (!n) return;
    n->loc.first_line  = fl;
    n->loc.first_column= fc;
    n->loc.last_line   = ll;
    n->loc.last_column = lc;
}

#endif
