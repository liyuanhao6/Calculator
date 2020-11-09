//
// Created by 黎袁昊 on 2020/10/28.
//

#include "Controleur.h"

Controleur *Controleur::instance = nullptr;

Controleur &Controleur::getInstance() {
    if (instance == nullptr) instance = new Controleur();
    return *instance;
}

void Controleur::executer() {
    std::string s;
    do {
        lirAff.affiche();
        std::cout << "?-";
        std::getline(std::cin, s);
        if (s == "Q")
            state = false;
        else
            commande(s);
    } while (state);
}

void Controleur::commande(const std::string &s) {
    std::string type = estQuelType(s);
    if (type == "Programme")
        estProgramme(s);
    else if (type == "Expression")
        estExpression(s);
    else if (type == "Symbol") {
        std::string temp = getSymbol(s);
        std::string newType = estQuelType(temp);
        lirAff.push(toLitterale(temp));
        if (newType == "Programme") estOperateur("EVAL");
    } else if (type == "OperateurNotParameter")
        estOperateur(s);
    else if (type == "OperateurUnaire")
        if (lirAff.taille() >= 1)
            estOperateur(s);
        else
            throw std::invalid_argument("pas assez d'arguments");
    else if (type == "OperateurBinaire")
        if (lirAff.taille() >= 2)
            estOperateur(s);
        else
            throw std::invalid_argument("pas assez d'arguments");
    else if (type == "Fraction")
        estFraction(s);
    else if (type == "Rationnelle")
        estRationnelle(s);
    else if (type == "Entiere")
        estEntiere(s);
    else
        throw std::invalid_argument("Erreur de format d'entree");
}

void Controleur::estOperateur(const std::string &s) {
    auto iter = OP.find(s);
    if (iter != OP.end())
        iter->second->Action();
    else {
        Operator *opt = toOperator(s);
        OP[opt->type_of_litterale()] = opt;
        auto new_iter = OP.find(s);
        new_iter->second->Action();
    }
}

void Controleur::setException(const std::string &s) { lirAff.setMessage(s); }

bool Controleur::getState() const { return state; }
