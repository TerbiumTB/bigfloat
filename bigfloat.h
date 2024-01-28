#ifndef VERY_LONG_FLOAT_BIGFLOAT_H
#define VERY_LONG_FLOAT_BIGFLOAT_H

#include <iostream>
#include <vector>
#include <ostream>


class bigfloat {
private:
    std::vector<int> _mantissa;
    long _exponent;
    bool _sign;
public:
    bigfloat();

    bigfloat(std::string &input);

    std::string toString();

};


#endif //VERY_LONG_FLOAT_BIGFLOAT_H
