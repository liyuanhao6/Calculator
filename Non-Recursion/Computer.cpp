#include "Computer.h"
ExpressionManager* ExpressionManager::instance = nullptr;
Expression::Expression(int inValue) : value(inValue) {}
bool Expression::operator==(const Expression& exp) const {
    if (this->value == exp.value)
        return true;
    else
        return false;
}
int Expression::getValue() const { return value; }
std::string Expression::toString() const { return std::to_string(value); }
ExpressionManager::~ExpressionManager() {
    if (this->exps)
        for (unsigned int i = 0; i < this->nb; i++) delete this->exps[i];
    delete[] this->exps;
    this->nb = 0;
    this->nbMax = 0;
}
void ExpressionManager::agrandissementCapacite() {
    Expression** newExpressions = new Expression*[this->nbMax + 5];
    for (unsigned int i = 0; i < this->nb; i++) newExpressions[i] = this->exps[i];
    Expression** oldExpressions = this->exps;
    this->exps = newExpressions;
    delete[] oldExpressions;
    this->nbMax += 5;
}
ExpressionManager& ExpressionManager::getInstance() {
    if (instance == nullptr) instance = new ExpressionManager;
    return *instance;
}
void ExpressionManager::destroyInstance() {
    delete instance;
    instance = nullptr;
}
Expression& ExpressionManager::addExpression(int v) {
    if (this->nb >= this->nbMax) this->agrandissementCapacite();
    this->exps[this->nb++] = new Expression(v);
    return *this->exps[this->nb - 1];
}
void ExpressionManager::removeExpression(Expression& e) {
    for (unsigned int i = 0; i < this->nb; i++) {
        if (*this->exps[i] == e) {
            for (unsigned int j = i; j < nb - 1; j++) this->exps[j] = this->exps[j + 1];
            this->nb--;
        }
    }
}
void Item::setExpression(Expression& exp) { this->exp = &exp; }
Expression& Item::getExpression() const {
    if (this->exp == nullptr) throw("the Item of Expression is NULL!");
    return *this->exp;
}
void Item::raz() { this->exp = nullptr; }
void Pile::agrandissementCapacite() {
    Item* newItems = new Item[this->nbMax + 5];
    for (unsigned int i = 0; i < this->nb; i++) newItems[i] = this->items[i];
    Item* oldItems = this->items;
    this->items = newItems;
    delete[] oldItems;
    this->nbMax += 5;
}
Pile::Pile() : items(nullptr), nb(0), nbMax(0), nbAffiche(4), message("") {}
Pile::~Pile() {
    if (this->items) delete[] items;
    this->nb = 0;
    this->nbMax = 0;
    this->nbAffiche = 0;
    this->message = "";
}
void Pile::affiche() const {
    system("clear");
    std::cout << std::endl << "*********************************************" << std::endl;
    std::cout << "M : " << this->message << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    for (size_t i = this->nbAffiche; i > 0; i--)
        if (i <= this->nb)
            std::cout << i << ": " << this->items[i - 1].getExpression().toString() << std::endl;
        else
            std::cout << i << ": " << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
}
void Pile::push(Expression& e) {
    if (this->nb >= this->nbMax) this->agrandissementCapacite();
    for (unsigned int i = this->nb; i > 0; i--) this->items[i] = this->items[i - 1];
    this->items[0].setExpression(e);
    this->nb++;
}
void Pile::pop() {
    for (unsigned int i = 0; i < this->nb - 1; i++) this->items[i] = this->items[i + 1];
    this->nb--;
}
bool Pile::estVide() const { return this->nb == 0 ? true : false; }
size_t Pile::taille() const { return this->nb; }
Expression& Pile::top() const { return this->items[0].getExpression(); }
void Pile::setMessage(const std::string& m) { this->message = m; }
std::string Pile::getMessage() const { return this->message; }
void Pile::setNbItemsToAffiche(size_t n) { this->nbAffiche = n; }
Controleur::Controleur(Pile& expAff) : expAff(expAff) {}
void Controleur::commande(const std::string& c) {
    if (estUnNombre(c)) {
        this->expAff.push(this->expManager.addExpression(stoi(c)));
        this->expAff.setMessage("");
    } else {
        if (estUnOperateur(c)) {
            if (this->expAff.taille() >= 2) {
                int v1 = this->expAff.top().getValue();
                this->expManager.removeExpression(this->expAff.top());
                this->expAff.pop();
                int v2 = this->expAff.top().getValue();
                this->expManager.removeExpression(this->expAff.top());
                this->expAff.pop();
                int res;
                if (c == "+") res = v2 + v1;
                if (c == "-") res = v2 - v1;
                if (c == "*") res = v2 * v1;
                if (c == "/") res = v2 / v1;
                Expression& e = this->expManager.addExpression(res);
                this->expAff.push(e);
                this->expAff.setMessage("");
            } else {
                this->expAff.setMessage("Erreur : pas assez d'arguments");
            }
        } else
            this->expAff.setMessage("Erreur : commande inconnue");
    }
}
void Controleur::executer() {
    std::string c;
    do {
        this->expAff.affiche();
        std::cout << "?-";
        std::cin >> c;
        if (c != "Q") this->commande(c);
    } while (c != "Q");
}
bool estUnOperateur(const std::string& s) {
    if (s == "+") return true;
    if (s == "-") return true;
    if (s == "*") return true;
    if (s == "/") return true;
    return false;
}
bool estUnNombre(const std::string& s) {
    try {
        std::stoi(s);
        return true;
    } catch (...) {
        return false;
    }
}