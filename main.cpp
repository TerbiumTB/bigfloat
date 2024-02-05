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

lli powmod (lli a, lli b, lli p) {
    lli res = 1;
    while (b)
        if (b & 1)
            res = lli (res * a % p),  --b;
        else
            a = lli (a * a % p),  b >>= 1;
    return res;
}

void generator (lli p) {
    std::vector<lli> fact;
    lli phi = p-1,  n = phi;
    for (auto i=2; i*i<=n; ++i)
        if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back (n);

    for (lli res=2; res<=p; ++res) {
        bool ok = true;
        for (size_t i=0; i<fact.size() && ok; ++i)
            ok &= powmod (res, phi / fact[i], p) != 1;
        if (ok)  std::cout << (res) << std::endl;
    }
//    return -1;
}


int main() {
////    std::vector<int> a = {13213, 213534, 12712, 13819, 91763};
    auto b = bigfloat("2.1");
    auto a = bigfloat("123.1");
    auto c = a*b;
////    a += b;
//
//
////    auto b = bigfloat("10000000001");
//    auto c = a + 1;
////    c *= -1;
////    c -= 2_bf;
////    auto d = c--;
////    ++d;
////    d += -1.2_bf;
////    std::cout << (a < b) << std::endl;
//    std::cout <<  (P > BASE) << std::endl;
////    std::cout <<  d.to_string() << std::endl;
    std::cout << c.to_string() << std::endl;
////    std::cout << (c & ~(0b111 << 27)) << std::endl;
//    return 0;
//auto w = generator(P);
//digit_t w = W;
//for (auto i = 0; i < 30; ++i){
//    w = (w*w < P) ? w*w : w*w % P;
//    std::cout << w << std::endl;
}


//    generator(P);
//(2267742733 * 2267742733) <

//}



