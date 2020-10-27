#ifndef _COMPUTER_H
#define _COMPUTER_H
#include <iostream>
#include <string>
class ComputerException {
    std::string info;

public:
    ComputerException(const std::string& str) : info(str) {}
    std::string getInfo() const { return info; }
};
class Expression {
private:
    int value;
    Expression(int inValue = 0);

public:
    bool operator==(const Expression& exp) const;
    int getValue() const;
    std::string toString() const;
    friend class ExpressionManager;
};
class ExpressionManager {
private:
    static ExpressionManager* instance;
    ExpressionManager() = default;
    ExpressionManager(const ExpressionManager& expManager) = delete;
    ExpressionManager& operator=(const ExpressionManager& expManager) = delete;
    ~ExpressionManager();
    Expression** exps = nullptr;
    size_t nb = 0;
    size_t nbMax = 0;
    void agrandissementCapacite();

public:
    static ExpressionManager& getInstance();
    static void destroyInstance();
    Expression& addExpression(int v);
    void removeExpression(Expression& e);
};
class Item {
private:
    Expression* exp;

public:
    Item() = default;
    void setExpression(Expression& exp);
    Expression& getExpression() const;
    void raz();
};
class Pile {
    Item* items;
    size_t nb;
    size_t nbMax;
    size_t nbAffiche;
    std::string message;
    void agrandissementCapacite();

public:
    Pile();
    ~Pile();
    void affiche() const;
    void push(Expression& e);
    void pop();
    bool estVide() const;
    size_t taille() const;
    Expression& top() const;
    void setMessage(const std::string& m);
    std::string getMessage() const;
    void setNbItemsToAffiche(size_t n);
};
class Controleur {
private:
    ExpressionManager& expManager = ExpressionManager::getInstance();
    Pile expAff;

public:
    Controleur(Pile& expAff);
    void commande(const std::string& c);
    void executer();
};
bool estUnOperateur(const std::string& s);
bool estUnNombre(const std::string& s);
#endif