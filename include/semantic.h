#pragma once

#include "ast.h"
#include "symbol_table.h"
#include <vector>
#include <string>

class SemanticAnalyzer {
public:
    SemanticAnalyzer() = default;

    bool analyze(const ASTNode* root);
    const std::vector<std::string>& getErrors() const { return errors; }

private:
    SymbolTable symbolTable;
    std::vector<std::string> errors;

    void visit(const ASTNode* node);
    void visitProgram(const ProgramNode* node);
    void visitBlock(const BlockNode* node);
    void visitVarDecl(const VarDeclNode* node);
    void visitAssign(const AssignNode* node);
    void visitPrint(const PrintNode* node);
    void visitIf(const IfNode* node);
    void visitBinaryOp(const BinaryOpNode* node);
    void visitUnaryOp(const UnaryOpNode* node);
    void visitVariable(const VariableNode* node);

    void addError(int line, const std::string& msg);
};
