#include "Litterale.h"

/*simplifier*/
LitteraleNumerique *LitteraleEntiere::simplifier() {
    return new LitteraleEntiere(this->entiere);
}

LitteraleNumerique *LitteraleFraction::simplifier() {
    if (this->denominateur == 1) {
        return new LitteraleEntiere(this->numerateur);
    } else {
        return new LitteraleFraction(this->numerateur, this->denominateur);
    }
}

LitteraleNumerique *LitteraleRationnelle::simplifier() {
    if (this->partie_decimale == 0) {
        return new LitteraleEntiere(this->partie_entiere);
    } else {
        return new LitteraleRationnelle(this->partie_entiere, this->partie_decimale);
    }
}

/*constructeur*/
LitteraleFraction::LitteraleFraction(int n, int d) : numerateur(n), denominateur(d) {
    simplification();
}

LitteraleEntiere::LitteraleEntiere(int m) : entiere(m) {}

void LitteraleFraction::simplification() {
    if (numerateur == 0) {
        denominateur = 1;
        return;
    }
    if (denominateur == 0) throw ComputerException("créer une Fraction avec le value zéro de dénominateur");
    int a = numerateur, b = denominateur;
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (a != b) {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    numerateur /= a;
    denominateur /= a;
    if (denominateur < 0) {
        denominateur = -denominateur;
        numerateur = -numerateur;
    }
}


/*tostring*/
std::string LitteraleRationnelle::toString() {
    return std::to_string(this->partie_entiere) + "." + std::to_string(this->partie_decimale);
}

std::string LitteraleProgramme::toString() {
    std::stringstream ss;
    std::string str_all;
    for (auto a : this->elements) {
        ss << a->toString() << " ";
    }
    str_all = ss.str();
    size_t num_last_not_space = str_all.find_last_not_of(" ");
    str_all.erase(num_last_not_space + 1);
    return "[" + str_all + "]";
}

/*litteralprogramme operateur de list*/
void LitteraleProgramme::elementsPushBack(Litterale *newlitterale) {
    this->elements.push_back(newlitterale);
}

void LitteraleProgramme::elementsPopBack() {
    this->elements.pop_back();
}

void LitteraleProgramme::elementsSupprimer(Litterale *sup) {
    auto it = find(this->elements.begin(), this->elements.end(), sup);
    if (it == this->elements.end()) {
        throw ComputerException("L'élément à supprimer n'exisite pas!");
    } else {
        this->elements.erase(it);
    }
}


/*toDouble*/
double LitteraleEntiere::toDouble() const {
    return static_cast<double>(this->entiere);
}

double LitteraleFraction::toDouble() const {
    return static_cast<double>(this->numerateur) / static_cast<double>(this->denominateur);
}

double LitteraleRationnelle::toDouble() const {
    std::stringstream ss;
    int size_decimale;
    std::string str_decimale;
    ss << this->partie_decimale;
    ss >> str_decimale;
    size_decimale = str_decimale.size();
    return this->partie_entiere + this->partie_decimale * pow(10, -size_decimale);
}


/*toRationnelle*/
LitteraleNumerique *toRationnelle(double num_double) {
    if (num_double == static_cast<int>(num_double))
        return new LitteraleEntiere(static_cast<int>(num_double));
    bool sign = true;
    if (num_double < 0) {
        num_double = -num_double;
        sign = false;
    }
    std::stringstream ss;
    int num_partie_entiere;
    int num_mantisse;
    char ch;
    ss << num_double;
    ss >> num_partie_entiere >> ch >> num_mantisse;
    if (sign == false) {
        num_partie_entiere = -num_partie_entiere;
    }
    return LitteraleRationnelle(num_partie_entiere, num_mantisse).simplifier();

}


std::string getFirstLitterale(std::string str) {
    if (str.find("!=") == 0 || str.find("<=") == 0 || str.find(">=") == 0) {
        std::string str_first(str, 0, 2);
        return str_first;
    } else if (str.find("=") == 0 || str.find("<") == 0 || str.find(">") == 0) {
        std::string str_first(str, 0, 1);
        return str_first;
    } else if (str.find("[") == 0) {
        size_t left = 0, right = 0;
        do {
            left = str.find_first_of("[", left + 1);
            right = str.find_first_of("]", right + 1);
        } while (left < right);
        std::string str_first(str, 0, right + 1);
        return str_first;
    } else {
        std::string str_first;
        std::stringstream ss;
        ss << str;
        ss >> str_first;
        if (str_first.find("[") < str_first.size()) {
            str_first = str_first.erase(str_first.find("[") - 1);
        }
        if (str_first == "\"EXIT\"") {
            throw ComputerException("");
        }
        return str_first;
    }
}

LitteraleNumerique *getFraction(int n, int d) { return new LitteraleFraction(n, d); }