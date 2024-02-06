#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "bigfloat.h"

//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 git hub token


//bigfloat_lib operator ""_bf(long double number) {
//    return {std::to_string(number)};
//}
//bigfloat_lib operator ""_bf(unsigned long long number) {
//    return {std::to_string(number)};
//}


bigfloat pi(lli precision=bigfloat::precision()){
    bigfloat k = 0_bf;
    auto x = 8*k;

    bigfloat a = x + 1;
    bigfloat b = x + 4;
    bigfloat c = x + 5;
    bigfloat d = x + 6;


}
int main() {
//    std::vector<int> a = {13213, 213534, 12712, 13819, 91763};
    auto b = bigfloat("10.123451231231243561243541256345612437561243651243675124376512436541263541623412675346125436512431762123456124356");
    auto a = bigfloat("-17.123456789123456789");
    bigfloat::precision() = 10;
//    a += b;


//    auto b = bigfloat_lib("10000000001");
    auto c = a+b;
//    c *= -1;
//    c -= 2_bf;
//    auto d = c--;
//    ++d;
//    d += -1.2_bf;
//    std::cout << (a < b) << std::endl;
//    std::cout <<  (10 == -a) << std::endl;
//    std::cout <<  d.to_string() << std::endl;
//b += a;

    std::cout << a << std::endl;
//    std::cout << (c & ~(0b111 << 27)) << std::endl;
    return 0;
}



