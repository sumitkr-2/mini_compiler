#include "semantic.h"
#include <sstream>

void SemanticAnalyzer::addError(int line, const std::string& msg) {
    std::ostringstream oss;
    oss << "Semantic Error (line " << line << "): " << msg;
    errors.push_back(oss.str());
}

bool SemanticAnalyzer::analyze(const ASTNode* root) {
    errors.clear();
    symbolTable = SymbolTable();
    if (root) {
        visit(root);
    }
    return errors.empty();
}

void SemanticAnalyzer::visit(const ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NodeType::PROGRAM:
            visitProgram(static_cast<const ProgramNode*>(node));
            break;
        case NodeType::BLOCK:
            visitBlock(static_cast<const BlockNode*>(node));
            break;
        case NodeType::VAR_DECL:
            visitVarDecl(static_cast<const VarDeclNode*>(node));
            break;
        case NodeType::ASSIGN:
            visitAssign(static_cast<const AssignNode*>(node));
            break;
        case NodeType::PRINT:
            visitPrint(static_cast<const PrintNode*>(node));
            break;
        case NodeType::IF:
            visitIf(static_cast<const IfNode*>(node));
            break;
        case NodeType::BINARY_OP:
            visitBinaryOp(static_cast<const BinaryOpNode*>(node));
            break;
        case NodeType::UNARY_OP:
            visitUnaryOp(static_cast<const UnaryOpNode*>(node));
            break;
        case NodeType::VARIABLE:
            visitVariable(static_cast<const VariableNode*>(node));
            break;
        case NodeType::NUMBER:
            break;
    }
}

void SemanticAnalyzer::visitProgram(const ProgramNode* node) {
    for (const auto& stmt : node->statements) {
        visit(stmt.get());
    }
}

void SemanticAnalyzer::visitBlock(const BlockNode* node) {
    symbolTable.enterScope();
    for (const auto& stmt : node->statements) {
        visit(stmt.get());
    }
    symbolTable.exitScope();
}

void SemanticAnalyzer::visitVarDecl(const VarDeclNode* node) {
    if (symbolTable.isDeclaredInCurrentScope(node->name)) {
        addError(node->line, "Redeclaration of variable '" + node->name + "' in the same scope.");
    } else {
        symbolTable.declare(node->name, "int", node->line);
    }

    if (node->init_expr) {
        visit(node->init_expr.get());
    }
}

void SemanticAnalyzer::visitAssign(const AssignNode* node) {
    if (!symbolTable.isDeclared(node->name)) {
        addError(node->line, "Assignment to undeclared variable '" + node->name + "'.");
    }
    if (node->expr) {
        visit(node->expr.get());
    }
}

void SemanticAnalyzer::visitPrint(const PrintNode* node) {
    if (node->expr) {
        visit(node->expr.get());
    }
}

void SemanticAnalyzer::visitIf(const IfNode* node) {
    if (node->condition) {
        visit(node->condition.get());
    }
    if (node->then_branch) {
        visit(node->then_branch.get());
    }
    if (node->else_branch) {
        visit(node->else_branch.get());
    }
}

void SemanticAnalyzer::visitBinaryOp(const BinaryOpNode* node) {
    if (node->left) {
        visit(node->left.get());
    }
    if (node->right) {
        visit(node->right.get());
    }

    if (node->op == "/") {
        if (node->right && node->right->type == NodeType::NUMBER) {
            const auto* numNode = static_cast<const NumberNode*>(node->right.get());
            if (numNode->value == 0) {
                addError(node->line, "Division by zero.");
            }
        }
    }
}

void SemanticAnalyzer::visitUnaryOp(const UnaryOpNode* node) {
    if (node->expr) {
        visit(node->expr.get());
    }
}

void SemanticAnalyzer::visitVariable(const VariableNode* node) {
    if (!symbolTable.isDeclared(node->name)) {
        addError(node->line, "Undeclared variable '" + node->name + "'.");
    }
}
