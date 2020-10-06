#include "Token.h"

std::tuple<double, std::string> parseNumber(std::string input) {
    double result = 0;     // 结果
    bool firstDot = true;  // 第一次遇到小数点
    std::string numstr;    // 数字字符串
    while (true) {
        // 如果为空
        if (input.empty()) break;
        char ch = input.front();  // 输入字符串的首字符
        // 如果为数字字符或第一个小数点
        if ((ch >= '0' && ch <= '9') || (ch == '.' && firstDot)) {
            numstr.push_back(ch);
            input.erase(input.begin());
            if (ch == '.') firstDot = false;
        } else
            break;
    }
    return {std::stod(numstr), input};
}

std::tuple<Token, std::string> tokenize(std::string input) {
    Token tk;  // 符号
    char ch;   // 输入字符串首字符
    // 去除空格
    do {
        // 如果为空
        if (input.empty()) {
            tk.type = TokenType::End;
            return {tk, ""};
        } else {
            // 拿到input最开头的字符
            ch = input.front();
            // 把input的开头剔除
            input.erase(input.begin());
        }
    } while (ch == ' ');
    // 去除第一个非空格字符生成新token用于返回
    switch (ch) {
    // 定义符号
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
        tk.type = TokenType(ch);
        break;
    // 定义数字
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        tk.type = TokenType::Number;
        // 把ch重新添加到input的开头
        input.insert(input.begin(), ch);
        std::tie(tk.value, input) = parseNumber(input);
        break;
    // 错误
    default:
        throw std::runtime_error{"error: invalid symbol!\n"};
        break;
    }
    return {tk, input};
}