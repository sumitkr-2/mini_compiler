#include "symbol_table.h"

SymbolTable::SymbolTable() {
    enterScope(); // global scope
}

void SymbolTable::enterScope() {
    scopes.emplace_back();
}

void SymbolTable::exitScope() {
    if (scopes.size() > 1) {
        scopes.pop_back();
    }
}

bool SymbolTable::declare(const std::string& name, const std::string& type, int line) {
    if (scopes.empty()) {
        enterScope();
    }
    auto& current = scopes.back();
    if (current.find(name) != current.end()) {
        return false;
    }
    current[name] = Symbol{name, type, line};
    return true;
}

bool SymbolTable::isDeclaredInCurrentScope(const std::string& name) const {
    if (scopes.empty()) return false;
    return scopes.back().find(name) != scopes.back().end();
}

bool SymbolTable::isDeclared(const std::string& name) const {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        if (it->find(name) != it->end()) {
            return true;
        }
    }
    return false;
}

const Symbol* SymbolTable::lookup(const std::string& name) const {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto found = it->find(name);
        if (found != it->end()) {
            return &found->second;
        }
    }
    return nullptr;
}
