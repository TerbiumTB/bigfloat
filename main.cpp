#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "bigfloat.h"

//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 git hub token


//bigfloat operator ""_bf(long double number) {
//    return {std::to_string(number)};
//}
//bigfloat operator ""_bf(unsigned long long number) {
//    return {std::to_string(number)};
//}
int main() {
//    std::vector<int> a = {13213, 213534, 12712, 13819, 91763};
    auto b = bigfloat("0.0000032300004");
    auto a = bigfloat("999999999999999999.0000");
//    a += b;


//    auto b = bigfloat("10000000001");
    auto c = a + 1;
//    c *= -1;
//    c -= 2_bf;
//    auto d = c--;
//    ++d;
//    d += -1.2_bf;
//    std::cout << (a < b) << std::endl;
    std::cout <<  (10 == -a) << std::endl;
//    std::cout <<  d.to_string() << std::endl;
    std::cout << c.to_string() << std::endl;
//    std::cout << (c & ~(0b111 << 27)) << std::endl;
    return 0;
}



