#ifndef VERY_LONG_FLOAT_BIGFLOAT_H
#define VERY_LONG_FLOAT_BIGFLOAT_H

#include <iostream>
#include <vector>
#include <ostream>
#include <sstream>

#define BASE 1e9
#define CAPACITY 10
#define mod(a, m) ((m - (a)%m)%m)
typedef unsigned long long digit_t;
typedef long long int lli;


class bigfloat {
private:
    std::vector<digit_t> _mantissa;
    std::vector<digit_t> _integer;
    lli _exponent;
    bool _signum;

    /*number is represented in (_signum)*_integer + 10^(-CAPACITY*_exponent)*0._float
     * so for example _integer = {1}
     * _exponent = 1
     * _float = {2}
     * _signum = true
     * equals 1.00000000002*/

    static digit_t to_digit(char);
    static void add_digit(digit_t&, char);

    static std::string num2string(digit_t);
    static std::string fnum2string(digit_t);

    static digit_t move_pos(digit_t&, unsigned);

    void discard_zeros();

public:

    bigfloat();

    bigfloat(std::string);

    std::string to_string();

    int sign();
    int greatest();
    int lowest();

    bigfloat operator-();

    digit_t operator[] (lli) const;


    friend bigfloat operator+(bigfloat, bigfloat);


    friend bool operator==(const bigfloat&, const bigfloat&);

    friend std::strong_ordering operator<=>(const bigfloat&, const bigfloat&);

};



#endif //VERY_LONG_FLOAT_BIGFLOAT_H
