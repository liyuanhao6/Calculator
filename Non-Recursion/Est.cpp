//
// Created on 2020/11/7.
//
#include "Est.h"

void estProgramme(const std::string &s) {
    lirAff.push(toLitterale(s));
    lirAff.setMessage("Ajouter des donnees de type de Programme"); 
}

void estExpression(const std::string &s) {
    lirAff.push(toLitterale(s));
    lirAff.setMessage("Ajouter des donnees de type de Expression");
}

void estFraction(const std::string &s) {
    unsigned int pos = s.find('/');
    unsigned int len = s.length();
    std::string t1 = s.substr(pos + 1, len - pos);
    int denominateur = std::stoi(t1);
    std::string t2 = s.substr(0, pos);
    int numerateur = std::stoi(t2);
    lirAff.push(getFraction(numerateur, denominateur));
    lirAff.setMessage("Ajouter des donnees de type de Fraction"); 
}

void estRationnelle(const std::string &s) {
    auto temp = std::stod(s);
    lirAff.push(toNumerique(temp));
    lirAff.setMessage("Ajouter des donnees de type de Rationnelle"); 
}

void estEntiere(const std::string &s) {
    auto temp = std::stod(s);
    lirAff.push(toNumerique(temp));
    lirAff.setMessage("Ajouter des donnees de type de Entiere"); 
}


