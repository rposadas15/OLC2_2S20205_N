#ifndef AST_H
#define AST_H

struct ASTNode {
    char* kind;
    char* value;
    struct ASTNode* left;
    struct ASTNode* right;
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

#endif
