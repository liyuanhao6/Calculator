#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdexcept>
#include <string>
#include <tuple>

#include "Token.h"

// 逐个解析 使用tuple返回多个值
std::tuple<double, std::string> parseExpress(std::string input);

#endif  // __PARSER_H__
