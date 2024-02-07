
#include <iostream>
#include "bigfloat.h"


bigfloat pi(lli precision = bigfloat::precision()) {
    precision += 10;
    auto previous_precision = bigfloat::precision();
    bigfloat::precision() = precision;
    bigfloat pi = 0_bf;

    bigfloat power = 1_bf;

    lli a = 1;
    lli b = 4;
    lli c = 5;
    lli d = 6;

    for (auto k = 0; k < precision; ++k) {
        pi += (power * (4_bf / a - 2_bf / b - 1_bf / c - 1_bf / d));
        power /= 16;
        a += 8;
        b += 8;
        c += 8;
        d += 8;
    }

    bigfloat::precision() -= 10;
//    std::cout << pi << std::endl;
    bigfloat::precision() = previous_precision;
    return pi;
}

bigfloat pi() {
    bigfloat::precision() += 10;
    bigfloat pi = 0_bf;

    bigfloat power = 1_bf;

    lli a = 1;
    lli b = 4;
    lli c = 5;
    lli d = 6;

    for (auto k = 0; k < bigfloat::precision(); ++k) {
        pi += (power * (4_bf / a - 2_bf / b - 1_bf / c - 1_bf / d));
        power /= 16;
        a += 8;
        b += 8;
        c += 8;
        d += 8;
    }

    bigfloat::precision() -= 10;
    std::cout << pi << std::endl;
    return pi;
}

int main() {
    auto a = bigfloat("0.1");

    std::cout << pi(1000) << std::endl;
    return 0;
}