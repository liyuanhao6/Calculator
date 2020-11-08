//
// Created by 黎袁昊 on 2020/11/7.
//

#include "SymbolTable.h"

SymbolTable *SymbolTable::instance = nullptr;

SymbolTable &SymbolTable::getInstance() {
    if (instance == nullptr) instance = new SymbolTable();
    return *instance;
}

void SymbolTable::insert(const std::string &a, const std::string &b) {
    symbolTable.insert(std::map<std::string, std::string>::value_type(a, b));
}

void SymbolTable::remove(const std::string &a) {
    auto iter = symbolTable.find(a);
    if (iter != symbolTable.end())
        symbolTable.erase(iter);
}

const std::string getSymbol(const std::string &a, SymbolTable &s) {
    auto iter = s.symbolTable.find(a);
    return iter->second;
}

bool estExist(const std::string &a, SymbolTable &s) {
    auto iter = s.symbolTable.find(a);
    return !(iter == s.symbolTable.end());
}


