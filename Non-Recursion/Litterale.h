#ifndef PROJECT_LITTERALE_H
#define PROJECT_LITTERALE_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <utility>

class Litterale {
public:
    virtual std::string toString() = 0; // 获取字符串

    [[nodiscard]] virtual double toDouble() const { return 0; }; // 获取浮点数

    virtual ~Litterale() = default; // 虚析构函数
};

class LitteraleNumerique : public Litterale {
public:
    std::string toString() override = 0; // 获取字符串

    virtual LitteraleNumerique *simplifier() = 0; // 简化并且重新定义类型

    [[nodiscard]] double toDouble() const override = 0; // 获取浮点数
};

class LitteraleAtome : public Litterale {
private:
    std::string nom_atome; // atome

public:
    std::string toString() override { return nom_atome; } // 获取字符串

    explicit LitteraleAtome(std::string str_atome) : nom_atome(std::move(str_atome)) {} // 构造函数
};

class LitteraleExpression : public Litterale {
private:
    std::string nom_expression; // expression

public:
    std::string toString() override { return nom_expression; } // 获取字符串

    explicit LitteraleExpression(std::string expression) : nom_expression(std::move(expression)) {} // 构造函数
};

class LitteraleSymbol : public Litterale {
private:
    std::string nom_symbol;  // symbol

    std::map<std::string, std::string> symbolTable; // 存储STO关联符号

    static LitteraleSymbol *instance; // LitteraleSymbol

    LitteraleSymbol() = default; // 私有构造器

    ~LitteraleSymbol() override = default; // 私有析构器

public:
    std::string toString() override { return nom_symbol; } // 获取字符串

    LitteraleSymbol(const LitteraleSymbol &c) = delete; // 删除拷贝构造器

    LitteraleSymbol &operator=(const LitteraleSymbol &c) = delete; // 删除赋值运算符

    static LitteraleSymbol &getInstance(); // 返回LitteraleSymbol类单一对象

    void insert(const std::string &a, const std::string &b); // 插入一个关联对

    void remove(const std::string &a); // 删除一个关联对

    friend std::string getSymbol(const std::string &a, LitteraleSymbol &LS); // 获取关联对中的value

    friend bool estExist(const std::string &a, LitteraleSymbol &LS); // map中是否存在该关联对
};

class LitteraleProgramme : public Litterale {
private:
    std::list<Litterale *> elements;  // Litterale指针数组

public:
    LitteraleProgramme() = default; // 构造函数

    explicit LitteraleProgramme(std::string programme); // 构造函数

    std::string toString() override; // 转换为字符串

    Litterale *getFirstElement(); // 获得数组第一个元素并且删除该元素

    unsigned int getLength(); // 获得数组大小

    void elementsPushBack(Litterale *); // 加入数组最后
};

class LitteraleEntiere : public LitteraleNumerique {
private:
    int entiere;  // 整数

    friend class LitteraleFraction;  // 有理数类

    friend class LitteraleRationnelle;  // 实数类

    explicit LitteraleEntiere(int); // 私有构造器

    friend LitteraleNumerique *toNumerique(double); // 唯一能创建Entiere对象的函数

public:
    std::string toString() override { return std::to_string(entiere); } // 获取字符串

    LitteraleNumerique *simplifier() override; // 给toNumerique函数创建对象

    [[nodiscard]] double toDouble() const override; // 获取浮点数
};

class LitteraleFraction : public LitteraleNumerique {
private:
    int numerateur;    // 分子
    int denominateur;  // 分母

    LitteraleFraction(int n, int d); // 私有构造器

    friend LitteraleNumerique *toNumerique(double); // 能创建Fraction对象的函数

    friend LitteraleNumerique *getFraction(int, int); // 能创建Fraction对象的函数

public:
    std::string toString() override { // 获取字符串
        return std::to_string(numerateur) + "/" + std::to_string(denominateur);
    }

    LitteraleNumerique *simplifier() override; // 给toNumerique函数创建对象

    [[nodiscard]] double toDouble() const override; // 获取浮点数

    void simplification(); // 分数简化
};

class LitteraleRationnelle : public LitteraleNumerique {
private:
    int partie_entiere;   // 整数
    int partie_decimale;  // 小数

    LitteraleRationnelle(int e, int d) : partie_entiere(e), partie_decimale(d) {} // 私有构造器

    friend LitteraleNumerique *toNumerique(double); // 唯一能创建Rationnelle对象函数

public:
    std::string toString() override; // 获取字符串

    LitteraleNumerique *simplifier() override; // 给toNumerique函数创建对象

    [[nodiscard]] double toDouble() const override; // 获取浮点数
};

LitteraleNumerique *toNumerique(double); // 唯一能创建Numerique对象函数

LitteraleNumerique *getFraction(int, int); // 能创建Fraction对象的函数

Litterale *toLitterale(const std::string &s); // 转换成Litterale

std::string estQuelType(const std::string &s); // 判断是哪种类型

bool estUnOperateurNotParameter(const std::string &s); // 判断是否为无参数运算符

bool estUnOperateurUnaire(const std::string &s); // 判断是否为一元运算符

bool estUnOperateurBinaire(const std::string &s); // 判断是否为二元运算符

std::string getSymbol(const std::string &a, LitteraleSymbol &LS = LitteraleSymbol::getInstance()); // 获取关联对中的value

bool estExist(const std::string &a, LitteraleSymbol &LS = LitteraleSymbol::getInstance()); // map中是否存在该关联对

#endif  // PROJECT_LITTERALE_H