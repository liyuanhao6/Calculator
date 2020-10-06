#include "Parser.h"

// 因子
static std::tuple<double, std::string> parseFactor(std::string input) {
    double result;
    Token tk;
    // 解析第一个token
    std::tie(tk, input) = tokenize(input);

    switch (tk.type) {
    case TokenType::Number:
        result = std::get<double>(tk.value);
        break;
    case TokenType::Symbol: {
        auto search = getSymbolValue(std::get<std::string>(tk.value));
        // 检查是否定义
        if (search) {
            // 情况一 symbol是常量 Pi 或 e
            if (std::holds_alternative<double>(search.value()))
                result = std::get<double>(search.value());
            // 情况二 symbol是函数
            else {
                // 得到函数本体
                auto fun = std::get<std::function<double(double)>>(search.value());
                // 解析 (
                std::tie(tk, input) = tokenize(input);
                if (tk.type != TokenType::Lp) throw std::runtime_error("bad syntax: need a (\n");
                // 解析表达式
                double v;
                std::tie(v, input) = parseExpress(input);
                // 解析 )
                std::tie(tk, input) = tokenize(input);
                if (tk.type != TokenType::Rp) throw std::runtime_error("bad syntax: need a )\n");
                result = fun(v);
            }
        } else
            throw std::runtime_error("bad syntax: undefined symbol" +
                                     std::get<std::string>(tk.value) + "\n");
        break;
    }
    case TokenType::Lp: {
        // 执行 ( E ) 里面的 E
        std::tie(result, input) = parseExpress(input);
        // 解析 )
        std::tie(tk, input) = tokenize(input);
        // 如果不为 )
        if (tk.type != TokenType::Rp) std::runtime_error("bad syntax: need a )\n");
        break;
    }
    default:
        // 语法错误 抛出异常
        throw std::runtime_error("bad syntax: need a number or a (\n");
        break;
    }
    return {result, input};
}
//
std::tuple<double, std::string> parseTerm(std::string input) {
    double result;
    // 1.翻译 T -> FR 中的 F
    std::tie(result, input) = parseFactor(input);

    // 2.翻译 T -> FR 中的 R
    bool loop = true;
    while (loop) {
        Token op;
        std::string res;
        double term;
        // 2.1 翻译R前是 * 或者 / 或者 null
        std::tie(op, res) = tokenize(input);
        switch (op.type) {
        case TokenType::Mul: {
            // 2.2 解析 *TR 中的 T
            std::tie(term, input) = parseFactor(res);
            // 根据乘法语义更新result的数值
            result *= term;
            break;
        }
        case TokenType::Div: {
            // 2.2 解析 /TR 中的 T
            std::tie(term, input) = parseFactor(res);
            // 不可以除以零
            if (term == 0.0) throw std::runtime_error("error: divided by zero!\n");
            // 根据除法语义更新result的数值
            result /= term;
            break;
        }
        default:
            // 退出循环
            loop = false;
            break;
        }
    }
    return {result, input};
}
// 表达式
// E -> TR
// R -> +TR | -TR | null
std::tuple<double, std::string> parseExpress(std::string input) {
    double result;
    // 1.翻译 E -> TR 中的 T
    std::tie(result, input) = parseTerm(input);

    // 2.翻译 E -> TR 中的 R
    bool loop = true;
    while (loop) {
        Token op;
        std::string res;
        double term;
        // 2.1 翻译R前是 + 或者 - 或者 null
        std::tie(op, res) = tokenize(input);
        switch (op.type) {
        case TokenType::Plus: {
            // 2.2 解析 +TR 中的 T
            std::tie(term, input) = parseTerm(res);
            // 根据加法语义更新result的数值
            result += term;
            break;
        }
        case TokenType::Minus: {
            // 2.2 解析 -TR 中的 T
            std::tie(term, input) = parseTerm(res);
            // 根据减法语义更新result的数值
            result -= term;
            break;
        }
        default:
            // 退出循环
            loop = false;
            break;
        }
    }
    return {result, input};
}