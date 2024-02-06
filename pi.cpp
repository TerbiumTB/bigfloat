
#include <iostream>
#include "bigfloat.h"

bigfloat pi1(lli precision = bigfloat::precision()) {
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
//        std::cout << k << ':' << (4_bf / a - 2_bf / b - 1_bf / c - 1_bf / d) << ' ' << a << ' ' << b << ' ' << c << ' '
//                  << d << std::endl;
//        std::cout << k << ':' << 4_bf << '/' << a << '-' << 2_bf << '/' << b << '-' << 1_bf << '/' << c << '-' << 1_bf
//                  << '/' << d << std::endl;
////        std::cout <<  pi << std::endl;

        pi += (power * (4_bf / a - 2_bf / b - 1_bf / c - 1_bf / d));
        power /= 16;
        a += 8;
        b += 8;
        c += 8;
        d += 8;
    }
    bigfloat::precision() = previous_precision;
//    0.002180579380761778207631351733652991242706775665283203125
//    0.002180579380761776184114466999950753023177039990
    return pi;
}

int main() {
    auto a = bigfloat("0.1");
    bigfloat::precision() = 1000;
    bigfloat p1 = pi1();

    std::cout << p1 << std::endl;
    return 0;
}