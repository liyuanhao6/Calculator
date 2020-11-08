//
// Created by 黎袁昊 on 2020/11/7.
//

#ifndef PROJECT_PILE_H
#define PROJECT_PILE_H

#include "Litterale.h"
#include <vector>

class Pile {
private:
    std::vector<Litterale *> litterales;
    unsigned int nbAffiche = 4;
    std::string message;
    static Pile *instance; // 唯一LitteraleManager对象
    // 私有构造器
    Pile() = default;

    // 私有析构函数
    ~Pile() = default;

public:
    // 拷贝构造函数删除
    Pile(const Pile &optFac) = delete;

    // 赋值运算符删除
    Pile &operator=(const Pile &optFac) = delete;

    // 获取OperateurFactory对象
    static Pile &getInstance();

    // 删除OperateurFactory对象
    static void destroyInstance();

    void affiche() const;

    void push(Litterale *l);

    void pop();

    bool estVide() const;

    unsigned int taille() const;

    Litterale *top() const;

    void clear();

    void setMessage(const std::string &m);

    std::string getMessage() const;

    void setNbItemsToAffiche(size_t n);
};

#endif //PROJECT_PILE_H
