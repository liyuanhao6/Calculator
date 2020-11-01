#ifndef PROJECT_SYMBOLTABLE_H
#define PROJECT_SYMBOLTABLE_H

#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include "ComputerException.h"
#include <algorithm>
#include <cmath>
#include <utility>

class Litterale {
public:
    // 转换为字符串
    virtual std::string toString() = 0;

    // 转换为浮点数
    virtual double toDouble() const = 0;

    // 虚析构函数
    virtual ~Litterale() = default;
};

class LitteraleNumerique : public Litterale {

public:
    // 转换为字符串
    std::string toString() override = 0;

    // 提供创建对象接口
    virtual LitteraleNumerique *simplifier() = 0;

    // 提供浮点数
    double toDouble() const override = 0;
};

class LitteraleAtome : public Litterale {
private:
    std::string nom_atome; // atome

public:
    // 获取字符串
    std::string toString() override { return nom_atome; }

    // 构造函数
    explicit LitteraleAtome(std::string str_atome) : nom_atome(std::move(str_atome)) {}

};

class LitteraleExpression : public Litterale {
private:
    std::string nom_expression; // expression

public:
    // 获取字符串
    std::string toString() override { return nom_expression; }

    // 构造函数
    explicit LitteraleExpression(std::string expression) : nom_expression(std::move(expression)) {}

};

class LitteraleProgramme : public Litterale {
private:
    std::list<Litterale *> elements; // Litterale指针数组

public:
    // 构造函数
    LitteraleProgramme() = default;

    // 转换为字符串
    std::string toString() override;

    // 加入数组最后
    void elementsPushBack(Litterale *);

    // 删除数组最后
    void elementsPopBack();

    // 删除数组某个元素
    void elementsSupprimer(Litterale *);

};

class LitteraleEntiere : public LitteraleNumerique {
private:
    int entiere; // 整数

    friend class LitteraleFraction; // 有理数类

    friend class LitteraleRationnelle; // 实数类
    // 私有构造器
    explicit LitteraleEntiere(int);

    // 唯一能创建对象的函数
    friend LitteraleNumerique *toRationnelle(double);

public:
    // 获取整数
    int getEntiere() const { return entiere; }

    // 转换为字符串
    std::string toString() override { return std::to_string(entiere); }

    // 给toRationnelle函数创建对象
    LitteraleNumerique *simplifier() override;

    // 转换成浮点数
    double toDouble() const override;
};

class LitteraleFraction : public LitteraleNumerique {
private:
    int numerateur; // 分子
    int denominateur; // 分母
    // 私有构造器
    LitteraleFraction(int n, int d);

public:
    // 转换为字符串
    std::string toString() override { return std::to_string(numerateur) + "/" + std::to_string(denominateur); }

    // 转换为Entiere 或 Rationnelle
    LitteraleNumerique *simplifier() override;

    // 转换成浮点数
    double toDouble() const override;

    // 获取Fraction指针 唯一能创建对象函数
    friend LitteraleNumerique *getFraction(int n, int d);

    // 获取数值
    double getValue() const { return numerateur * (1.0) / denominateur; }

    // 获取分子
    int getNumerateur() const { return numerateur; }

    // 获取分母
    int getDenominateur() const { return denominateur; }

    // 分数简化
    void simplification();
};

class LitteraleRationnelle : public LitteraleNumerique {
private:
    int partie_entiere; // 整数
    int partie_decimale; // 小数
    // 私有构造器
    LitteraleRationnelle(int e, int d) : partie_entiere(e), partie_decimale(d) {}

    // 唯一能创建对象函数
    friend LitteraleNumerique *toRationnelle(double);

public:
    // 转换为字符串
    std::string toString() override;

    // 为toRationnelle函数创建对象
    LitteraleNumerique *simplifier() override;

    // 转换成浮点数
    double toDouble() const override;


};

LitteraleNumerique *getFraction(int n, int d);

LitteraleNumerique *toRationnelle(double);

#endif //PROJECT_SYMBOLTABLE_H