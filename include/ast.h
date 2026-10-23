#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>

enum class NodeType {
    PROGRAM,
    VAR_DECL,
    ASSIGN,
    PRINT,
    IF,
    BLOCK,
    BINARY_OP,
    UNARY_OP,
    NUMBER,
    VARIABLE
};

class ASTNode {
public:
    NodeType type;
    int line;

    ASTNode(NodeType t, int l) : type(t), line(l) {}
    virtual ~ASTNode() = default;
    virtual void print(int indent = 0) const = 0;
};

class ProgramNode : public ASTNode {
public:
    std::vector<std::unique_ptr<ASTNode>> statements;

    explicit ProgramNode(int l = 1) : ASTNode(NodeType::PROGRAM, l) {}
    void addStatement(ASTNode* stmt) {
        if (stmt) {
            statements.emplace_back(stmt);
        }
    }
    void print(int indent = 0) const override;
};

class BlockNode : public ASTNode {
public:
    std::vector<std::unique_ptr<ASTNode>> statements;

    explicit BlockNode(int l) : ASTNode(NodeType::BLOCK, l) {}
    void addStatement(ASTNode* stmt) {
        if (stmt) {
            statements.emplace_back(stmt);
        }
    }
    void print(int indent = 0) const override;
};

class VarDeclNode : public ASTNode {
public:
    std::string name;
    std::unique_ptr<ASTNode> init_expr;

    VarDeclNode(std::string n, ASTNode* init, int l)
        : ASTNode(NodeType::VAR_DECL, l), name(std::move(n)), init_expr(init) {}
    void print(int indent = 0) const override;
};

class AssignNode : public ASTNode {
public:
    std::string name;
    std::unique_ptr<ASTNode> expr;

    AssignNode(std::string n, ASTNode* e, int l)
        : ASTNode(NodeType::ASSIGN, l), name(std::move(n)), expr(e) {}
    void print(int indent = 0) const override;
};

class PrintNode : public ASTNode {
public:
    std::unique_ptr<ASTNode> expr;

    PrintNode(ASTNode* e, int l)
        : ASTNode(NodeType::PRINT, l), expr(e) {}
    void print(int indent = 0) const override;
};

class IfNode : public ASTNode {
public:
    std::unique_ptr<ASTNode> condition;
    std::unique_ptr<ASTNode> then_branch;
    std::unique_ptr<ASTNode> else_branch;

    IfNode(ASTNode* cond, ASTNode* then_b, ASTNode* else_b, int l)
        : ASTNode(NodeType::IF, l), condition(cond), then_branch(then_b), else_branch(else_b) {}
    void print(int indent = 0) const override;
};

class BinaryOpNode : public ASTNode {
public:
    std::string op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

    BinaryOpNode(std::string o, ASTNode* l_node, ASTNode* r_node, int l)
        : ASTNode(NodeType::BINARY_OP, l), op(std::move(o)), left(l_node), right(r_node) {}
    void print(int indent = 0) const override;
};

class UnaryOpNode : public ASTNode {
public:
    std::string op;
    std::unique_ptr<ASTNode> expr;

    UnaryOpNode(std::string o, ASTNode* e, int l)
        : ASTNode(NodeType::UNARY_OP, l), op(std::move(o)), expr(e) {}
    void print(int indent = 0) const override;
};

class NumberNode : public ASTNode {
public:
    int value;

    NumberNode(int v, int l)
        : ASTNode(NodeType::NUMBER, l), value(v) {}
    void print(int indent = 0) const override;
};

class VariableNode : public ASTNode {
public:
    std::string name;

    VariableNode(std::string n, int l)
        : ASTNode(NodeType::VARIABLE, l), name(std::move(n)) {}
    void print(int indent = 0) const override;
};
