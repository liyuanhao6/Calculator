//
// Created by 黎袁昊 on 2020/10/28.
//

#ifndef PROJECT_CONTROLEUR_H
#define PROJECT_CONTROLEUR_H

#include <iostream>
#include <cmath>
#include "LitteralManager.h"
#include "Est.h"
#include <vector>


class Controleur {
private:
    LitteraleManager &lirManager = LitteraleManager::getInstance(); // LitteraleManager类唯一对象
    std::vector<Litterale *> lirAff; // Litterale指针数组
    std::string message; // 信息

public:
    // 构造函数
    Controleur(std::vector<Litterale *> &lirAff);

    // 对信息进行赋值
    void setMessage(const std::string &m);

    // 获取信息
    std::string getMessage() const;

    // 打印输出格式
    void affiche() const;

    // 命令处理函数
    void commande(const std::string &c);

    // 执行函数
    void executer();
};

inline void Controleur::setMessage(const std::string &m) { message = m; }

inline std::string Controleur::getMessage() const { return message; }


#endif //PROJECT_CONTROLEUR_H
