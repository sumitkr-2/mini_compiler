%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "ast.h"

extern int yylex();
extern int yylineno;
extern FILE* yyin;

void yyerror(const char* s);

std::unique_ptr<ProgramNode> rootNode = nullptr;
int syntaxErrorCount = 0;
%}

%union {
    int int_val;
    char* str_val;
    ASTNode* node;
    BlockNode* block;
}

%token <int_val> NUMBER
%token <str_val> IDENTIFIER
%token KW_INT KW_PRINT KW_IF KW_ELSE
%token OP_EQ OP_NEQ OP_LE OP_GE OP_LT OP_GT

%type <node> stmt var_decl assignment print_stmt if_stmt expr
%type <block> stmt_list block

%nonassoc LOWER_THAN_ELSE
%nonassoc KW_ELSE

%left OP_EQ OP_NEQ
%left OP_LT OP_LE OP_GT OP_GE
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

program:
    stmt_list {
        rootNode = std::make_unique<ProgramNode>(1);
        if ($1) {
            for (auto& s : $1->statements) {
                rootNode->statements.push_back(std::move(s));
            }
            delete $1;
        }
    }
;

stmt_list:
    stmt_list stmt {
        if ($2) {
            $1->addStatement($2);
        }
        $$ = $1;
    }
    | /* empty */ {
        $$ = new BlockNode(yylineno);
    }
;

stmt:
    var_decl ';' { $$ = $1; }
    | assignment ';' { $$ = $1; }
    | print_stmt ';' { $$ = $1; }
    | if_stmt { $$ = $1; }
    | block { $$ = $1; }
    | ';' { $$ = nullptr; }
;

var_decl:
    KW_INT IDENTIFIER {
        $$ = new VarDeclNode($2, nullptr, yylineno);
        free($2);
    }
    | KW_INT IDENTIFIER '=' expr {
        $$ = new VarDeclNode($2, $4, yylineno);
        free($2);
    }
;

assignment:
    IDENTIFIER '=' expr {
        $$ = new AssignNode($1, $3, yylineno);
        free($1);
    }
;

print_stmt:
    KW_PRINT expr {
        $$ = new PrintNode($2, yylineno);
    }
;

if_stmt:
    KW_IF '(' expr ')' stmt %prec LOWER_THAN_ELSE {
        $$ = new IfNode($3, $5, nullptr, yylineno);
    }
    | KW_IF '(' expr ')' stmt KW_ELSE stmt {
        $$ = new IfNode($3, $5, $7, yylineno);
    }
;

block:
    '{' stmt_list '}' {
        $$ = $2;
    }
;

expr:
    NUMBER {
        $$ = new NumberNode($1, yylineno);
    }
    | IDENTIFIER {
        $$ = new VariableNode($1, yylineno);
        free($1);
    }
    | expr '+' expr {
        $$ = new BinaryOpNode("+", $1, $3, yylineno);
    }
    | expr '-' expr {
        $$ = new BinaryOpNode("-", $1, $3, yylineno);
    }
    | expr '*' expr {
        $$ = new BinaryOpNode("*", $1, $3, yylineno);
    }
    | expr '/' expr {
        $$ = new BinaryOpNode("/", $1, $3, yylineno);
    }
    | expr OP_EQ expr {
        $$ = new BinaryOpNode("==", $1, $3, yylineno);
    }
    | expr OP_NEQ expr {
        $$ = new BinaryOpNode("!=", $1, $3, yylineno);
    }
    | expr OP_LT expr {
        $$ = new BinaryOpNode("<", $1, $3, yylineno);
    }
    | expr OP_LE expr {
        $$ = new BinaryOpNode("<=", $1, $3, yylineno);
    }
    | expr OP_GT expr {
        $$ = new BinaryOpNode(">", $1, $3, yylineno);
    }
    | expr OP_GE expr {
        $$ = new BinaryOpNode(">=", $1, $3, yylineno);
    }
    | '-' expr %prec UMINUS {
        $$ = new UnaryOpNode("-", $2, yylineno);
    }
    | '(' expr ')' {
        $$ = $2;
    }
;

%%

void yyerror(const char* s) {
    std::cerr << "Syntax Error (line " << yylineno << "): " << s << std::endl;
    syntaxErrorCount++;
}
