//
// Created by 黎袁昊 on 2020/11/7.
//
#include "Est.h"

void estProgramme(const std::string &s) {
    lirAff.push(toLitterale(s));
    lirAff.setMessage("添加Programme类型"); //todo
}

void estExpression(const std::string &s) {
    lirAff.push(toLitterale(s));
    lirAff.setMessage("添加Expression类型"); //todo
}

void estFraction(const std::string &s) {
    unsigned int pos = s.find('/');
    unsigned int len = s.length();
    std::string t1 = s.substr(pos + 1, len - pos);
    int denominateur = std::stoi(t1);
    std::string t2 = s.substr(0, pos);
    int numerateur = std::stoi(t2);
    lirAff.push(getFraction(numerateur, denominateur));
    lirAff.setMessage("添加Fraction类型"); //todo
}

void estRationnelle(const std::string &s) {
    auto temp = std::stod(s);
    lirAff.push(toRationnelle(temp));
    lirAff.setMessage("添加Rationnelle类型"); //todo
}

void estEntiere(const std::string &s) {
    auto temp = std::stod(s);
    lirAff.push(toRationnelle(temp));
    lirAff.setMessage("添加Entiere类型"); //todo
}


