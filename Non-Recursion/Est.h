//
// Created by 黎袁昊 on 2020/10/29.
//

#ifndef PROJECT_EST_H
#define PROJECT_EST_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <optional>
#include <variant>
#include "SymbolTable.h"

// 判断是哪个符号
std::optional<std::variant<double, std::function<double(double)>>>
estQuelSymbol(const std::string symbol, const std::string str);

// 判断是哪个函数
std::variant<double, std::function<double(double)>> estQuelFunction(const std::string symbol, const std::string str);

// 判断是哪个常量
double estQuelConst(const std::string symbol);

// 判断是否为一元操作符
bool estUnOperateurUnaire(const std::string &s);

// 判断是否为二元操作符
bool estUnOperateurBinaire(const std::string &s);

// 判断是哪个类型
std::string estQuelType(const std::string &s);


#endif //PROJECT_EST_H
