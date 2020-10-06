#include <iostream>

#include "Parser.h"
#include "Token.h"

int main() {
    // std::string input = "1.23 + 2 * (1+2/5-4)";
    std::string input = "1 + 2 * 3";
    try {
        auto [result, res] = parseExpress(input);
        std::cout << result << std::endl;
    } catch (std::exception& e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}