#ifndef PROJECT_CONTROLEUR_H
#define PROJECT_CONTROLEUR_H

#include <iostream>
#include <map>
#include <vector>
#include "Pile.h"
#include "SymbolTable.h"
#include "Operateur.h"
#include "Est.h"
#include <stdexcept>

class Controleur {
private:
    Pile &lirAff = Pile::getInstance();
    static Controleur *instance;
    std::map<std::string, Operator *> OP;
    bool state = true;

    Controleur() = default;

    ~Controleur() = default;

    void estOperateur(const std::string &s);

public:
    Controleur(const Controleur &c) = delete;

    Controleur &operator=(const Controleur &c) = delete;

    static Controleur &getInstance();

    void executer();

    void commande(const std::string &s);

    void setException(const std::string &s);

    [[nodiscard]] bool getState() const;
};

#endif //PROJECT_CONTROLEUR_H