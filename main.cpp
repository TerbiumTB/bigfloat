#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
//#include "bigfloat.h"
//#include "pi.h"
#include "bigfloat_lib/bigfloat.h"
#include "pi_lib/pi.h"

//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 git hub token

using namespace Bigfloat;
//bigfloat_lib operator ""_bf(long double number) {
//    return {std::to_string(number)};
//}
//bigfloat_lib operator ""_bf(unsigned long long number) {
//    return {std::to_string(number)};
//}


int main() {
//    std::vector<int> a = {13213, 213534, 12712, 13819, 91763};
//    auto b = bigfloat("10.123451231231243561243541256345612437561243651243675124376512436541263541623412675346125436512431762123456124356");
    auto a = bigfloat(1, 100);
    auto b = bigfloat("1.11111111111111111111");
    auto d = bigfloat(4);

//    bigfloat::precision() = 10;
//    a += b;

//auto c = divide(a, 6);

//    auto b = bigfloat_lib("10000000001");
//    auto c = a+b;
//    c *= -1;
//    c -= 2_bf;
//    auto d = c--;
//    ++d;
//    d += -1.2_bf;
//    std::cout << (a < b) << std::endl;
//    std::cout <<  (10 == -a) << std::endl;
//    std::cout <<  d.to_string() << std::endl;
//b += a;

    std::cout << b - d << std::endl;
//    std::cout << (c & ~(0b111 << 27)) << std::endl;
    return 0;
}


