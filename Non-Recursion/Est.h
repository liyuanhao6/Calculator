//
// Created on 2020/11/7.
//

#ifndef PROJECT_EST_H
#define PROJECT_EST_H
#include <iostream>
#include <string>

#include "Pile.h"

static Pile &lirAff = Pile::getInstance(); // Pile类单一接口

void estProgramme(const std::string &s); // 生成Programme类型数据并压栈

void estExpression(const std::string &s); // 生成Expression类型数据并压栈

void estFraction(const std::string &s); // 生成Fraction类型数据并压栈

void estRationnelle(const std::string &s); // 生成Rationnelle类型数据并压栈

void estEntiere(const std::string &s); // 生成Entiere类型数据并压栈

#endif  // PROJECT_EST_H
