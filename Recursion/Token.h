#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <functional>
#include <optional>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <variant>

enum class TokenType {
    Number,       // 数值
    Symbol,       // 符号 英文字母 a-z A-Z
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
    TokenType type;                                 // Token字符
    std::variant<double, std::string> value = 0.0;  // 数值
};
// 查找符号在符号表中的定义
std::optional<std::variant<double, std::function<double(double)>>> getSymbolValue(
    std::string symbol);
// 符号化
std::tuple<Token, std::string> tokenize(std::string input);

#endif  // __TOKEN_H__
