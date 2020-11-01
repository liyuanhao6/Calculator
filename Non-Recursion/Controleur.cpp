//
// Created by 黎袁昊 on 2020/10/28.
//

#include "Controleur.h"


Controleur::Controleur(std::vector<Litterale *> &lirAff) : lirAff(lirAff) {}

void Controleur::affiche() const {
    std::cout << std::endl << "*********************************************" << std::endl;
    std::cout << "M : " << message << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    for (size_t i = 4; i > 0; i--)
        if (i <= lirAff.size())
            std::cout << i << ": " << lirAff[lirAff.size() - i]->toString() << std::endl;
        else
            std::cout << i << ": " << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
}

void Controleur::commande(const std::string &c) {
    std::string type = estQuelType(c);
    if (type == "Programme") {

    } else if (type == "Expression") {
        auto ConstNum = std::get<double>(estQuelFunction(c, "Const"));
        lirAff.push_back(lirManager.addLitterale(toRationnelle(ConstNum)));
        setMessage("");
    } else if (type == "Atome") {
        if (estUnOperateurUnaire(c)) {
            if (lirAff.size() >= 1) {
                auto fun = std::get<std::function<double(double)>>(estQuelFunction(c, "UnaireFunction"));
                double value = lirAff[lirAff.size() - 1]->toDouble();
                lirManager.removeLitterale(lirAff[lirAff.size() - 1]);
                lirAff.pop_back();
                double res = fun(value);
                lirAff.push_back(lirManager.addLitterale(toRationnelle(res)));
                setMessage("");
            } else
                this->setMessage("Erreur : pas assez d'arguments");
        } else if (estUnOperateurBinaire(c)) {
            if (this->lirAff.size() >= 2) {
                auto fun = std::get<std::function<double(double, double)>>(estQuelFunction(c, "BinaireFunction"));
                double value1 = lirAff[lirAff.size() - 1]->toDouble();
                lirManager.removeLitterale(lirAff[lirAff.size() - 1]);
                lirAff.pop_back();
                double value2 = lirAff[lirAff.size() - 1]->toDouble();
                lirManager.removeLitterale(lirAff[lirAff.size() - 1]);
                lirAff.pop_back();
                double res = fun(value2, value1);
                lirAff.push_back(lirManager.addLitterale(toRationnelle(res)));
                setMessage("");
            } else
                setMessage("Erreur : pas assez d'arguments");
        } else if (1) {}
    } else if (type == "Fraction") {
        unsigned int pos = c.find("/");
        unsigned int len = c.length();
        std::string t1 = c.substr(pos + 1, len - pos);
        double denominateur = std::stod(t1);
        std::string t2 = c.substr(0, pos);
        double numerateur = std::stod(t2);
        lirAff.push_back(lirManager.addLitterale(getFraction(numerateur, denominateur)));
        setMessage("");
    } else if (type == "Rationnelle") {
        auto num = std::stod(c);
        lirAff.push_back(lirManager.addLitterale(toRationnelle(num)));
        setMessage("");
    } else if (type == "Entiere") {
        auto temp = std::stod(c);
        lirAff.push_back(lirManager.addLitterale(toRationnelle(temp)));
        setMessage("");
    } else
        this->setMessage("Erreur : pas assez d'arguments");
//    } else if ("OperateurUnaire") {
//        if (expAff.size() >= 1) {
//            auto fun = estQuelFunction(c);
//            if (expAff[expAff.size() - 1]->getType() == "Double") {
//                double v1 = std::get<Real>(expAff[expAff.size() - 1]->getValue()).getReal();
//                expManager.removeExpression(*expAff[expAff.size() - 1]);
//                this->expAff.pop_back();
//                double res;
//                res = fun(v1);
//                this->expAff.push_back(this->expManager.addExpression(Real(res), "Double"));
//                this->setMessage("");
//            } else {
//                this->setMessage("Erreur : pas assez d'arguments");
//            }
//    } else if ("OperateurBinaire") {
//            if (this->expAff.taille() >= 2) {
//                double v1 = this->expAff.top().getValue();
//                this->expManager.removeTopExpression();
//                this->expAff.pop();
//                auto v2 = this->expAff.top().getValue();
//                this->expManager.removeTopExpression();
//                this->expAff.pop();
//                double res;
//                if (c == "+") res = v2 + v1;
//                if (c == "-") res = v2 - v1;
//                if (c == "*") res = v2 * v1;
//                if (c == "/") res = v2 / v1;    // ComputerException
//                if (c == "DIV") res = v2 / v1;  // ComputerException
//                if (c == "MOD") res = v2 % v1;  // ComputerException
//                if (c == "POW") res = pow(v2, v1);
//                if (c == "=") res = (v1 == v2);
//                if (c == "!=") res = (v1 != v2);
//                if (c == "<") res = (v1 < v2);
//                if (c == ">") res = (v1 > v2);
//                if (c == "<=") res = (v1 <= v2);
//                if (c == ">=") res = (v1 >= v2);
//                if (c == "AND") res = (v1 & v2);  // ComputerException
//                if (c == "OR") res = (v1 | v2);   // ComputerException
//                Expression &e = this->expManager.addExpression(res);
//                this->expAff.push(e);
//                this->expAff.setMessage("");
}

void Controleur::executer() {
    std::string c;
    do {
        this->affiche();
        std::cout << "?-";
        std::cin >> c;
        if (c != "Q") this->commande(c);
    } while (c != "Q");
}

