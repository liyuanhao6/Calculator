#include <iostream>

#include "Parser.h"
#include "Token.h"

int main() {
    std::string input = "sqrt(sin(PI / 6) * sin(PI / 6) + cos(PI /6) * cos(PI /6))";
    try {
        auto [result, res] = parseExpress(input);
        std::cout << result << std::endl;
    } catch (std::exception& e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}