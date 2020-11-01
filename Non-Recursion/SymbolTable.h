//
// Created by 黎袁昊 on 2020/10/30.
//

#ifndef PROJECT_SYMBOLTABLE_H
#define PROJECT_SYMBOLTABLE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <variant>

// 符号表
std::unordered_map<std::string, double>
        ConstTable{{"PI", atan(1.0) * 4},
                   {"e",  exp(1.0)}};

std::unordered_map<std::string, std::function<double(double)>>
        FunctionTable{{
                              {"NEG", [](double val) { return -val; }},
                              {"SQRT", [](double val) { return sqrt(val); }},
                              {"EXP", [](double val) { return exp(val); }},
                              {"LN", [](double val) { return log(val) / log(exp(1)); }},
                              {"COS", [](double val) { return cos(val); }},
                              {"SIN", [](double val) { return sin(val); }},
                              {"TAN", [](double val) { return tan(val); }},
                              {"ARCSIN", [](double val) { return asin(val); }},
                              {"ARCCOS", [](double val) { return acos(val); }},
                              {"ARCTAN", [](double val) { return atan(val); }},
                              {"NUM", [](double val) { return (val - int(val) == 0) ? val : val - int(val); }},
                              {"DEN", [](double val) { return (val - int(val) == 0) ? 1 : val - int(val); }},
                              {"NOT", [](double val) { return (!val); }}}};

std::unordered_map<std::string, std::variant<std::unordered_map<std::string, double>, std::unordered_map<std::string, std::function<double(double)>>>>
        SymbolTable{{"Const", ConstTable}, {"Function", FunctionTable}};


#endif //PROJECT_SYMBOLTABLE_H
