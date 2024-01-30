#ifndef VERY_LONG_FLOAT_BIGFLOAT_H
#define VERY_LONG_FLOAT_BIGFLOAT_H

#include <iostream>
#include <vector>
#include <ostream>
#include <sstream>
#include <cmath>

#define BASE (lli) 1e9
#define CAPACITY 9
#define mod(a, m) ((m - (a)%m)%m)
typedef unsigned long long digit_t;
typedef long long int lli;


class bigfloat {
private:
    std::vector<digit_t> _mantissa;
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

    digit_t operator[] (lli) const;
    constexpr digit_t& operator[] (lli);

    void discard_zeros();

public:

    bigfloat();

    bigfloat(std::string);

    std::string to_string();

    int sign() const;
    lli greatest() const;
    lli lowest();


    bigfloat operator-();

    friend bigfloat operator-( bigfloat, bigfloat);

    bigfloat& operator-=(bigfloat);

    const bigfloat& operator--();
    const bigfloat operator--(int);


    friend bigfloat operator+(bigfloat, bigfloat);

    bigfloat& operator+=(bigfloat);

    const bigfloat& operator++();
    const bigfloat operator++(int);


    friend bool operator==(const bigfloat&, const bigfloat&);

    friend std::strong_ordering operator<=>(const bigfloat&, const bigfloat&);

};

bigfloat operator ""_bf(long double);

bigfloat operator ""_bf(unsigned long long);

#endif //VERY_LONG_FLOAT_BIGFLOAT_H
