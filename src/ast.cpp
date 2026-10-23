#include "ast.h"

static void printIndent(int indent) {
    for (int i = 0; i < indent; ++i) {
        std::cout << "  ";
    }
}

void ProgramNode::print(int indent) const {
    printIndent(indent);
    std::cout << "ProgramNode\n";
    for (const auto& stmt : statements) {
        stmt->print(indent + 1);
    }
}

void BlockNode::print(int indent) const {
    printIndent(indent);
    std::cout << "BlockNode\n";
    for (const auto& stmt : statements) {
        stmt->print(indent + 1);
    }
}

void VarDeclNode::print(int indent) const {
    printIndent(indent);
    std::cout << "VarDeclNode (" << name << ", line " << line << ")\n";
    if (init_expr) {
        init_expr->print(indent + 1);
    }
}

void AssignNode::print(int indent) const {
    printIndent(indent);
    std::cout << "AssignNode (" << name << " = ...)\n";
    if (expr) {
        expr->print(indent + 1);
    }
}

void PrintNode::print(int indent) const {
    printIndent(indent);
    std::cout << "PrintNode\n";
    if (expr) {
        expr->print(indent + 1);
    }
}

void IfNode::print(int indent) const {
    printIndent(indent);
    std::cout << "IfNode\n";
    printIndent(indent + 1);
    std::cout << "Condition:\n";
    if (condition) condition->print(indent + 2);
    printIndent(indent + 1);
    std::cout << "Then:\n";
    if (then_branch) then_branch->print(indent + 2);
    if (else_branch) {
        printIndent(indent + 1);
        std::cout << "Else:\n";
        else_branch->print(indent + 2);
    }
}

void BinaryOpNode::print(int indent) const {
    printIndent(indent);
    std::cout << "BinaryOpNode (" << op << ")\n";
    if (left) left->print(indent + 1);
    if (right) right->print(indent + 1);
}

void UnaryOpNode::print(int indent) const {
    printIndent(indent);
    std::cout << "UnaryOpNode (" << op << ")\n";
    if (expr) expr->print(indent + 1);
}

void NumberNode::print(int indent) const {
    printIndent(indent);
    std::cout << "NumberNode (" << value << ")\n";
}

void VariableNode::print(int indent) const {
    printIndent(indent);
    std::cout << "VariableNode (" << name << ")\n";
}
