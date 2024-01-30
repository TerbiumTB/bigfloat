#ifndef VERY_LONG_FLOAT_BIGFLOAT_H
#define VERY_LONG_FLOAT_BIGFLOAT_H

#include <iostream>
#include <vector>
#include <ostream>
#include <sstream>
#include <format>

class bigfloat {
private:
    std::vector<unsigned> _mantissa;
    long _exponent;
    bool _signum;
    unsigned _precision;

    static void add_digit(int &, char);

    static int to_digit(char);

    static std::string num2string(unsigned);

    static unsigned scale(unsigned);

    static unsigned value(unsigned);

    static unsigned zeroes(unsigned);


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
