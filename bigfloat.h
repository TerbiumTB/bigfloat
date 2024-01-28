#ifndef VERY_LONG_FLOAT_BIGFLOAT_H
#define VERY_LONG_FLOAT_BIGFLOAT_H

#include <iostream>
#include <vector>
#include <ostream>
#include <sstream>


class bigfloat {
private:
    std::vector<unsigned> _mantissa;
    long _exponent;
    bool _sign;

    static void add_digit(int &, char);
    static int toDigit(char);
    static std::string num2string(unsigned );

public:
    bigfloat();

    bigfloat(std::string);

    std::string toString();


};


#endif //VERY_LONG_FLOAT_BIGFLOAT_H
