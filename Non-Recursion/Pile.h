//
// Created on 2020/11/7.
//

#ifndef PROJECT_PILE_H
#define PROJECT_PILE_H

#include <vector>

#include "Litterale.h"

class Pile {
private:
    std::vector<Litterale *> litterales; // Litterale指针数组
    unsigned int nbAffiche = 4; // 打印Litterale指针数组最大数量
    std::string message; // 显示运算及异常信息
    static Pile *instance;  // Pile类单一指针
    Pile() = default; // 私有构造器
    ~Pile() = default; // 私有析构函数

public:
    Pile(const Pile &optFac) = delete; // 删除拷贝构造器

    Pile &operator=(const Pile &optFac) = delete; // 删除赋值运算符

    static Pile &getInstance(); // 返回Pile类单一对象

    void affiche() const; // 打印计算器页面

    void push(Litterale *l); // 添加Litterale指针数组最后一个元素

    void pop(); // 删除Litterale指针数组最后一个元素

    [[nodiscard]] unsigned int taille() const; // Litterale指针数组大小

    [[nodiscard]] Litterale *top() const; // 返回Litterale指针数组最后一个元素

    void clear(); // 清空Litterale指针数组

    void setMessage(const std::string &m); // 设置运算及异常信息
};

#endif  // PROJECT_PILE_H
