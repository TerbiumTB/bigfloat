#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "bigfloat.h"

#include <string_view>

//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 git hub token


bigfloat operator ""_bf(long double number) {
    return {std::to_string(number)};
}
bigfloat operator ""_bf(unsigned long long number) {
    return {std::to_string(number)};
}
int main() {
//    auto a = bigfloat("1.99999999999999999");
    auto b = bigfloat("121780000000000000000");
//    auto c = a + b;
//    std::cout << a.to_string() << std::endl;
    std::cout << b.to_string() << std::endl;
//    std::cout << c.to_string() << std::endl;
//    std::cout << (c & ~(0b111 << 27)) << std::endl;
    return 0;
}