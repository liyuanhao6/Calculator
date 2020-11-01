//
// Created by 黎袁昊 on 2020/10/29.
//

#include "Est.h"

std::optional<std::variant<double, std::function<double(double)>>>
estQuelSymbol(const std::string symbol, const std::string str) {
    if (str == "Const") {
        auto iter1 = SymbolTable.find(str);
        if (iter1 != SymbolTable.end()) {
            auto table = std::get<std::unordered_map<std::string, double>>(iter1->second);
            auto iter2 = table.find(symbol);
            if (iter2 != table.end()) return {iter2->second};
            else return {};
        } else return {};
    } else if (str == "Function") {
        auto iter1 = SymbolTable.find(str);
        if (iter1 != SymbolTable.end()) {
            auto table = std::get<std::unordered_map<std::string, std::function<double(double)>>>(iter1->second);
            auto iter2 = table.find(symbol);
            if (iter2 != table.end()) return {iter2->second};
            else return {};
        } else return {};
    } else return {};
}

std::variant<double, std::function<double(double)>> estQuelFunction(const std::string symbol, const std::string str) {
    auto search = estQuelSymbol(symbol, str);
    if (search) {
        if (std::holds_alternative<double>(search.value())) {
            double result = std::get<double>(search.value());
            return result;
        } else {
            // 得到函数本体
            auto fun = std::get<std::function<double(double)>>(search.value());
            return fun;
        }
    } else
        throw std::runtime_error("bad syntax: undefined symbol");
}

std::string estQuelType(const std::string &s) {
    if (s.find("[") != std::string::npos) return "Programme";
    else if (s.find("\"") != std::string::npos) return "Expression";
    else if (estUnOperateurUnaire(s) || estUnOperateurBinaire(s)) return "Atome";
    else if (s.find("/") != std::string::npos) return "Fraction";
    else if (s.find(".") != std::string::npos) return "Rationnelle";
    else if ((std::stod(s) - int(std::stod(s))) == 0) return "Entiere";
    else throw ("输入错误");
}


bool estUnOperateurUnaire(const std::string &s) {
    if (s == "NEG") return true;
    if (s == "SQRT") return true;
    if (s == "EXP") return true;
    if (s == "LN") return true;
    if (s == "COS") return true;
    if (s == "SIN") return true;
    if (s == "TAN") return true;
    if (s == "ARCSIN") return true;
    if (s == "ARCCOS") return true;
    if (s == "ARCTAN") return true;
    if (s == "NUM") return true;
    if (s == "DEN") return true;
    if (s == "NOT") return true;
    if (s == "DROP") return true;
    return false;
}

bool estUnOperateurBinaire(const std::string &s) {
    if (s == "+") return true;
    if (s == "-") return true;
    if (s == "*") return true;
    if (s == "/") return true;
    if (s == "DIV") return true;
    if (s == "MOD") return true;
    if (s == "POW") return true;
    if (s == "=") return true;
    if (s == "!=") return true;
    if (s == "<") return true;
    if (s == ">") return true;
    if (s == "<=") return true;
    if (s == ">=") return true;
    if (s == "AND") return true;
    if (s == "OR") return true;
    return false;
}