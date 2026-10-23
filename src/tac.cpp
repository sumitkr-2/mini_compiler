#include "tac.h"
#include <sstream>

std::string TACInstruction::toString() const {
    switch (op) {
        case TACOp::ASSIGN:
            return result + " = " + arg1;
        case TACOp::ADD:
            return result + " = " + arg1 + " + " + arg2;
        case TACOp::SUB:
            return result + " = " + arg1 + " - " + arg2;
        case TACOp::MUL:
            return result + " = " + arg1 + " * " + arg2;
        case TACOp::DIV:
            return result + " = " + arg1 + " / " + arg2;
        case TACOp::NEG:
            return result + " = -" + arg1;
        case TACOp::EQ:
            return result + " = " + arg1 + " == " + arg2;
        case TACOp::NEQ:
            return result + " = " + arg1 + " != " + arg2;
        case TACOp::LT:
            return result + " = " + arg1 + " < " + arg2;
        case TACOp::LE:
            return result + " = " + arg1 + " <= " + arg2;
        case TACOp::GT:
            return result + " = " + arg1 + " > " + arg2;
        case TACOp::GE:
            return result + " = " + arg1 + " >= " + arg2;
        case TACOp::PRINT:
            return "print " + arg1;
        case TACOp::LABEL:
            return result + ":";
        case TACOp::GOTO:
            return "goto " + arg1;
        case TACOp::IF_FALSE_GOTO:
            return "ifFalse " + arg1 + " goto " + arg2;
    }
    return "";
}

std::string TACGenerator::newTemp() {
    return "t" + std::to_string(tempCount++);
}

std::string TACGenerator::newLabel() {
    return "L" + std::to_string(labelCount++);
}

void TACGenerator::emit(TACOp op, const std::string& res, const std::string& a1, const std::string& a2) {
    instructions.push_back({op, res, a1, a2});
}

std::vector<TACInstruction> TACGenerator::generate(const ASTNode* root) {
    instructions.clear();
    tempCount = 0;
    labelCount = 0;
    if (root) {
        generateStmt(root);
    }
    return instructions;
}

void TACGenerator::printInstructions(std::ostream& os) const {
    for (const auto& instr : instructions) {
        if (instr.op == TACOp::LABEL) {
            os << instr.toString() << "\n";
        } else {
            os << "    " << instr.toString() << "\n";
        }
    }
}

void TACGenerator::generateStmt(const ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NodeType::PROGRAM: {
            const auto* prog = static_cast<const ProgramNode*>(node);
            for (const auto& stmt : prog->statements) {
                generateStmt(stmt.get());
            }
            break;
        }
        case NodeType::BLOCK: {
            const auto* blk = static_cast<const BlockNode*>(node);
            for (const auto& stmt : blk->statements) {
                generateStmt(stmt.get());
            }
            break;
        }
        case NodeType::VAR_DECL: {
            const auto* decl = static_cast<const VarDeclNode*>(node);
            if (decl->init_expr) {
                std::string val = generateExpr(decl->init_expr.get());
                emit(TACOp::ASSIGN, decl->name, val);
            }
            break;
        }
        case NodeType::ASSIGN: {
            const auto* assign = static_cast<const AssignNode*>(node);
            std::string val = generateExpr(assign->expr.get());
            emit(TACOp::ASSIGN, assign->name, val);
            break;
        }
        case NodeType::PRINT: {
            const auto* prt = static_cast<const PrintNode*>(node);
            std::string val = generateExpr(prt->expr.get());
            emit(TACOp::PRINT, "", val);
            break;
        }
        case NodeType::IF: {
            const auto* ifNode = static_cast<const IfNode*>(node);
            std::string cond = generateExpr(ifNode->condition.get());
            std::string elseLabel = newLabel();
            std::string endLabel = newLabel();

            if (ifNode->else_branch) {
                emit(TACOp::IF_FALSE_GOTO, "", cond, elseLabel);
                generateStmt(ifNode->then_branch.get());
                emit(TACOp::GOTO, "", endLabel);
                emit(TACOp::LABEL, elseLabel);
                generateStmt(ifNode->else_branch.get());
                emit(TACOp::LABEL, endLabel);
            } else {
                emit(TACOp::IF_FALSE_GOTO, "", cond, endLabel);
                generateStmt(ifNode->then_branch.get());
                emit(TACOp::LABEL, endLabel);
            }
            break;
        }
        default:
            generateExpr(node);
            break;
    }
}

std::string TACGenerator::generateExpr(const ASTNode* node) {
    if (!node) return "";

    switch (node->type) {
        case NodeType::NUMBER: {
            const auto* num = static_cast<const NumberNode*>(node);
            return std::to_string(num->value);
        }
        case NodeType::VARIABLE: {
            const auto* var = static_cast<const VariableNode*>(node);
            return var->name;
        }
        case NodeType::UNARY_OP: {
            const auto* un = static_cast<const UnaryOpNode*>(node);
            std::string val = generateExpr(un->expr.get());
            std::string t = newTemp();
            emit(TACOp::NEG, t, val);
            return t;
        }
        case NodeType::BINARY_OP: {
            const auto* bin = static_cast<const BinaryOpNode*>(node);
            std::string left = generateExpr(bin->left.get());
            std::string right = generateExpr(bin->right.get());
            std::string t = newTemp();
            TACOp op = TACOp::ADD;
            if (bin->op == "+") op = TACOp::ADD;
            else if (bin->op == "-") op = TACOp::SUB;
            else if (bin->op == "*") op = TACOp::MUL;
            else if (bin->op == "/") op = TACOp::DIV;
            else if (bin->op == "==") op = TACOp::EQ;
            else if (bin->op == "!=") op = TACOp::NEQ;
            else if (bin->op == "<") op = TACOp::LT;
            else if (bin->op == "<=") op = TACOp::LE;
            else if (bin->op == ">") op = TACOp::GT;
            else if (bin->op == ">=") op = TACOp::GE;

            emit(op, t, left, right);
            return t;
        }
        default:
            return "";
    }
}
