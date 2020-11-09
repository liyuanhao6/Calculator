//
// Created on 2020/11/7.
//

#ifndef PROJECT_EST_H
#define PROJECT_EST_H
#include <iostream>
#include <string>
#include "Pile.h"

static Pile &lirAff = Pile::getInstance();

void estProgramme(const std::string &s);

void estExpression(const std::string &s);

void estFraction(const std::string &s);

void estRationnelle(const std::string &s);

void estEntiere(const std::string &s);

#endif //PROJECT_EST_H
