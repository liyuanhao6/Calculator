//
// Created on 2020/11/7.
//

#ifndef PROJECT_EST_H
#define PROJECT_EST_H
#include <iostream>
#include <string>

#include "Pile.h"

static Pile &lirAff = Pile::getInstance(); //  interface unique de class pile

void estProgramme(const std::string &s); // Les donnees de type Programme sont generees et stockees("push")

void estExpression(const std::string &s); // Les donnees de type Expression sont generees et stockees("push")

void estFraction(const std::string &s); // Les donnees de type Fraction sont generees et stockees("push")

void estRationnelle(const std::string &s); // Les donnees de type Rationnelle sont generees et stockees("push")

void estEntiere(const std::string &s); // Les donnees de type Entiere sont generees et stockees("push")

#endif  // PROJECT_EST_H
