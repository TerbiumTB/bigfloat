#ifndef VERY_LONG_FLOAT_BIGFLOAT_H
#define VERY_LONG_FLOAT_BIGFLOAT_H

#include <iostream>
#include <vector>
#include <ostream>
#include <sstream>

class bigfloat {
private:
    std::vector<char> _mantissa;
    long _exponent;
    bool _signum;

    static char to_digit(char);

    static std::string num2string(unsigned);


    void discard_zeros();

public:

    bigfloat();

    bigfloat(std::string);

    std::string to_string();

    bigfloat operator-();

//    int operator[] (int) const;

    bigfloat operator+(bigfloat);

    std::strong_ordering operator<=>(bigfloat) const;

    bool operator==(bigfloat) const;

};


#endif //VERY_LONG_FLOAT_BIGFLOAT_H
