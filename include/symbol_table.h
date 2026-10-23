#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

struct Symbol {
    std::string name;
    std::string type;
    int line;
};

class SymbolTable {
public:
    SymbolTable();

    void enterScope();
    void exitScope();

    bool declare(const std::string& name, const std::string& type, int line);
    bool isDeclaredInCurrentScope(const std::string& name) const;
    bool isDeclared(const std::string& name) const;
    const Symbol* lookup(const std::string& name) const;

private:
    std::vector<std::unordered_map<std::string, Symbol>> scopes;
};
