#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include "ast.h"
#include "semantic.h"
#include "tac.h"

extern FILE* yyin;
extern int yyparse();
extern std::unique_ptr<ProgramNode> rootNode;
extern int syntaxErrorCount;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [--ast] [--tac] <source_file>\n";
        return 1;
    }

    std::string filename;
    bool dumpAST = false;
    bool dumpTAC = true;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--ast" || arg == "-ast") {
            dumpAST = true;
        } else if (arg == "--tac" || arg == "-tac") {
            dumpTAC = true;
        } else if (arg == "-h" || arg == "--help") {
            std::cout << "Mini Compiler\n";
            std::cout << "Usage: " << argv[0] << " [options] <source_file>\n";
            std::cout << "Options:\n";
            std::cout << "  --ast    Print Abstract Syntax Tree\n";
            std::cout << "  --tac    Print Three-Address Code (default)\n";
            std::cout << "  --help   Show help\n";
            return 0;
        } else {
            filename = arg;
        }
    }

    if (filename.empty()) {
        std::cerr << "Error: No input file specified.\n";
        return 1;
    }

    FILE* file = std::fopen(filename.c_str(), "r");
    if (!file) {
        std::cerr << "Error: Cannot open file '" << filename << "'\n";
        return 1;
    }

    yyin = file;
    int parseResult = yyparse();
    std::fclose(file);

    if (parseResult != 0 || syntaxErrorCount > 0 || !rootNode) {
        std::cerr << "Compilation failed: Syntax errors found.\n";
        return 1;
    }

    SemanticAnalyzer semantic;
    if (!semantic.analyze(rootNode.get())) {
        for (const auto& err : semantic.getErrors()) {
            std::cerr << err << "\n";
        }
        std::cerr << "Compilation failed: Semantic errors found.\n";
        return 1;
    }

    if (dumpAST) {
        std::cout << "=== Abstract Syntax Tree ===\n";
        rootNode->print();
        std::cout << "============================\n";
    }

    if (dumpTAC) {
        TACGenerator tacGen;
        tacGen.generate(rootNode.get());
        std::cout << "=== Three-Address Code ===\n";
        tacGen.printInstructions();
        std::cout << "==========================\n";
    }

    return 0;
}
