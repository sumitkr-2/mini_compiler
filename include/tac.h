#pragma once

#include "ast.h"
#include <string>
#include <vector>
#include <iostream>

enum class TACOp {
    ASSIGN,
    ADD,
    SUB,
    MUL,
    DIV,
    NEG,
    EQ,
    NEQ,
    LT,
    LE,
    GT,
    GE,
    PRINT,
    LABEL,
    GOTO,
    IF_FALSE_GOTO
};

struct TACInstruction {
    TACOp op;
    std::string result;
    std::string arg1;
    std::string arg2;

    std::string toString() const;
};

class TACGenerator {
public:
    TACGenerator() = default;

    std::vector<TACInstruction> generate(const ASTNode* root);
    void printInstructions(std::ostream& os = std::cout) const;
    const std::vector<TACInstruction>& getInstructions() const { return instructions; }

private:
    int tempCount = 0;
    int labelCount = 0;
    std::vector<TACInstruction> instructions;

    std::string newTemp();
    std::string newLabel();

    void emit(TACOp op, const std::string& res = "", const std::string& a1 = "", const std::string& a2 = "");

    void generateStmt(const ASTNode* node);
    std::string generateExpr(const ASTNode* node);
};
