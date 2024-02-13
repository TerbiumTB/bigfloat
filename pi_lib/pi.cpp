#include "bigfloat.h"
#include <iostream>


bigfloat pi(lli precision) {
    precision += 10;
    bigfloat pi = bigfloat(0, precision);

    bigfloat power = bigfloat(1, precision);

    lli a = 1;
    lli b = 4;
    lli c = 5;
    lli d = 6;

    for (auto k = 0; k < precision; ++k) {

        auto s = divide(bigfloat(4, precision), a) - divide(bigfloat(2, precision), b) - divide(bigfloat(1, precision), c) - divide(bigfloat(1, precision), d);
//        std::cout << k << ':' << s*power << std::endl;
        s *= power;
        std::cout << k << ':' << s << std::endl;
        pi += s;
        power = divide(power, 16);
        a += 8;
        b += 8;
        c += 8;
        d += 8;
    }


    return pi;
}
//000000000000000000000000000026534859014499243700227047150865200761266082893133268015680370973358714858723951244087610495490964864682774772369969807804629472448190003440460227324138031690381467342376708984375
//00000000000000000000000000002653485901449924370022704715086520076126608289313326801568037097335871485872395124
//000000000000000000000000000026534859014499243700227047150865200761266082893133268015680370973358714858723951244087610495490964864682774772369969807804629472448190003440460227324138031690381467342376708984375