//
// Created by 黎袁昊 on 2020/10/28.
//

#ifndef PROJECT_COMPUTEREXCEPTION_H
#define PROJECT_COMPUTEREXCEPTION_H

#include <iostream>

class ComputerException {
private:
    std::string info; // 错误信息

public:
    // 构造函数
    ComputerException(const std::string &str);

    // 获取错误信息
    std::string getInfo() const;
};


#endif //PROJECT_COMPUTEREXCEPTION_H
