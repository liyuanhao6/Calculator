//
// Created by 黎袁昊 on 2020/10/28.
//

#include "ComputerException.h"

ComputerException::ComputerException(const std::string &str) : info(str) {}

std::string ComputerException::getInfo() const { return info; }