#ifndef VERY_LONG_FLOAT_BIGFLOAT_H
#define VERY_LONG_FLOAT_BIGFLOAT_H

#include <iostream>
#include <vector>
#include <ostream>
#include <sstream>
#include <cmath>
#include <compare>

#define BASE (digit_t) 1e9
#define CAPACITY 9
#define mod(a, m) ((m - (a)%m)%m)

typedef unsigned long long digit_t;
typedef long long int lli;

//16.18659547830967073703080
//16.18659547830966513513861950
//16,186595478309671
//16,186595478309671

class bigfloat {
private:
    static lli _precision;
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

    static void add_digit(digit_t &, char);

    static std::string num2string(digit_t);

    static std::string fnum2string(digit_t);

    digit_t operator[](lli) const;

    constexpr digit_t &operator[](lli);

    void discard_zeros();

public:

    bigfloat();

    bigfloat(std::string);

    static lli precision(lli);

    static lli precision();

    static bool valuable(lli);

    static lli border();

    lli accuracy() const;


    std::string to_string();

    int sign() const;

    lli greatest() const;

    lli lowest() const;


    bigfloat operator-() const;

    friend bigfloat operator-(bigfloat, const bigfloat &);

    bigfloat &operator-=(const bigfloat &);

    friend bigfloat operator-(bigfloat, lli);

    friend bigfloat operator-(lli, bigfloat);

    bigfloat &operator-=(lli);

    const bigfloat &operator--();

    const bigfloat operator--(int);


    friend bigfloat operator+(bigfloat, const bigfloat &);

    bigfloat &operator+=(const bigfloat &);

    friend bigfloat operator+(bigfloat, lli);

    friend bigfloat operator+(lli, bigfloat);

    bigfloat &operator+=(lli);

    const bigfloat &operator++();

    const bigfloat operator++(int);


    friend bigfloat operator*(bigfloat, const bigfloat &);

    bigfloat &operator*=(const bigfloat &);

    friend bigfloat operator*(bigfloat, lli);

    friend bigfloat operator*(lli, bigfloat);

    bigfloat &operator*=(lli);


    friend bigfloat operator/(bigfloat, lli);

    bigfloat &operator/=(lli);

    friend bigfloat operator/(bigfloat, bigfloat);

    bigfloat &operator/=(bigfloat);


    friend bool operator==(const bigfloat &, const bigfloat &);

    friend std::strong_ordering operator<=>(const bigfloat &, const bigfloat &);

    friend bool operator==(lli, const bigfloat &);

    friend std::strong_ordering operator<=>(lli, const bigfloat &);

    friend bool operator==(const bigfloat &, lli);

    friend std::strong_ordering operator<=>(const bigfloat &, lli);

};

bigfloat operator ""_bf(long double);

bigfloat operator ""_bf(unsigned long long);

#endif //VERY_LONG_FLOAT_BIGFLOAT_H
