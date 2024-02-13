#include "bigfloat.h"


using namespace Bigfloat;

bigfloat pi(lli precision) {
    precision += 10;

    bigfloat pi = bigfloat(0, precision);

    bigfloat power = bigfloat(1, precision);

    bigfloat a0 = {4, precision};
    bigfloat b0 = {2, precision};
    bigfloat c0 = {1, precision};
    bigfloat d0 = {1, precision};

    lli a = 1;
    lli b = 4;
    lli c = 5;
    lli d = 6;

    for (auto k = 0; k < precision && power != 0; ++k) {

        auto s = divide(a0, a) - divide(b0, b) - divide(c0, c) - divide(d0, d);
        s *= power;
        pi += s;
        power = divide(power, 16);
        a += 8;
        b += 8;
        c += 8;
        d += 8;
    }

    return pi;
}