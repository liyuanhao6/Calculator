//
// Created by 黎袁昊 on 2020/10/28.
//

#ifndef PROJECT_LITTERALMANAGER_H
#define PROJECT_LITTERALMANAGER_H

#include <iostream>
#include <list>
#include "Litterale.h"

class LitteraleManager {
private:
    static LitteraleManager *instance; // 唯一LitteraleManager对象
    // 私有构造器
    LitteraleManager() = default;

    // 私有析构函数
    ~LitteraleManager() = default;

    // Litterale指针数组
    std::list<Litterale *> litterales;

public:
    // 拷贝构造函数删除
    LitteraleManager(const LitteraleManager &expManager) = delete;

    // 赋值运算符删除
    LitteraleManager &operator=(const LitteraleManager &expManager) = delete;

    // 获取LitteraleManager对象
    static LitteraleManager &getInstance();

    // 删除LitteraleManager对象
    static void destroyInstance();

    // 添加Litterale
    Litterale *addLitterale(Litterale *l);

    // 删除Litterale
    void removeLitterale(Litterale *l);
};


#endif //PROJECT_LITTERALMANAGER_H
