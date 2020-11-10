#ifndef PROJECT_CONTROLEUR_H
#define PROJECT_CONTROLEUR_H

#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

#include "Est.h"
#include "Operateur.h"
#include "Pile.h"

class Controleur {
private:
    Pile &lirAff = Pile::getInstance(); // Pile类单一接口
    static Controleur *instance; // Controleur类单一指针
    std::map<std::string, Operator *> OP; // 运算符map std::map<std::string, Operator *>
    bool state = true; // 计算器运行状态

    Controleur() = default; // 私有构造器

    ~Controleur() = default; // 私有析构器

    void estOperateur(const std::string &s); // 识别运算符，存入运算符map，并且进行运算

public:
    Controleur(const Controleur &c) = delete; // 删除拷贝构造器

    Controleur &operator=(const Controleur &c) = delete; // 删除赋值运算符

    static Controleur &getInstance(); // 返回Controleur类单一对象

    void executer(); // 执行函数

    void commande(const std::string &s); // 接受指令函数

    void setException(const std::string &s); // 输出异常

    [[nodiscard]] bool getState() const; // 获取计算器当前状态
};

#endif  // PROJECT_CONTROLEUR_H