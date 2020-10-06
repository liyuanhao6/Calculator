#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <stdexcept>
#include <string>
#include <tuple>
enum class TokenType {
    Number,       // 数值
    End,          // 结束符
    Error,        // 错误符
    Plus = '+',   // 加号
    Minus = '-',  // 减号
    Mul = '*',    // 乘号
    Div = '/',    // 除号
    Lp = '(',     // 左括号
    Rp = ')',     // 右括号
};

class Token {
public:
    TokenType type;  // Token字符
    double value;    // 数值
    Token() : value(0.0){};
};

// 解析数字
std::tuple<double, std::string> parseNumber(std::string input);
// 符号化
std::tuple<Token, std::string> tokenize(std::string input);

#endif  // __TOKEN_H__
