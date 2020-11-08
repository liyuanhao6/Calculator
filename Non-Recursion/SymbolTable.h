//
// Created on 2020/11/7.
//

#ifndef PROJECT_SYMBOLTABLE_H
#define PROJECT_SYMBOLTABLE_H

#include <iostream>
#include <map>


class SymbolTable {
private:
    std::map<std::string, std::string> symbolTable;

    static SymbolTable *instance;

    SymbolTable() = default;

    ~SymbolTable() = default;

public:
    SymbolTable(const SymbolTable &c) = delete;

    SymbolTable &operator=(const SymbolTable &c) = delete;

    static SymbolTable &getInstance();

    void insert(const std::string &a, const std::string &b);

    void remove(const std::string &a);

    friend const std::string getSymbol(const std::string &a, SymbolTable &s);

    friend bool estExist(const std::string &a, SymbolTable &s);
};

const std::string getSymbol(const std::string &a, SymbolTable &s = SymbolTable::getInstance());

bool estExist(const std::string &a, SymbolTable &s = SymbolTable::getInstance());


#endif //PROJECT_SYMBOLTABLE_H
