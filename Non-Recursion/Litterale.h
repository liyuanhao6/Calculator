#ifndef PROJECT_LITTERALE_H
#define PROJECT_LITTERALE_H

#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <utility>
#include "SymbolTable.h"

class Litterale {
public:
    // 转换为字符串
    virtual std::string toString() = 0;

    // 转换为浮点数
    virtual double toDouble() const { return 0;};

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

    explicit LitteraleProgramme(std::string programme);

    // 转换为字符串
    std::string toString() override;

    // 获得第一个元素
    Litterale * getFirstElement();

    // 获得数组大小
    unsigned int getLength();

    // 加入数组最后
    void elementsPushBack(Litterale *);

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

Litterale *toLitterale(const std::string &s);

std::string estQuelType(const std::string &s);

bool estUnOperateurNotParameter(const std::string &s);

bool estUnOperateurUnaire(const std::string &s);

bool estUnOperateurBinaire(const std::string &s);


#endif //PROJECT_LITTERALE_H