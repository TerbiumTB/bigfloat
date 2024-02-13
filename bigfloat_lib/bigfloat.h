#ifndef VERY_LONG_FLOAT_BIGFLOAT_H
#define VERY_LONG_FLOAT_BIGFLOAT_H


#include <vector>
#include <sstream>
#include <compare>

#define BASE (digit_t) 1e9
#define CAPACITY 9
#define mod(a, m) ((m - (a)%m)%m)

typedef unsigned long long digit_t;
typedef long long int lli;

class bigfloat {
private:
    lli _precision;
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

    void discard_zeros();

    digit_t operator[](lli) const;
    constexpr digit_t &operator[](lli);

    lli border() const;
public:

    bigfloat();

    bigfloat(lli, lli);

//    bigfloat(float, lli);

    explicit bigfloat(std::string);

    explicit bigfloat(lli);

//    explicit bigfloat(float);

//    static lli precision(lli);

    lli & precision();


    std::string to_string() const;
    std::string to_string(lli) const;

    friend std::ostream& operator<<(std::ostream&,const bigfloat &);

    int sign() const;

    lli greatest() const;
    lli lowest() const;



    bigfloat operator-() const;

    friend bigfloat operator-(const bigfloat &, const bigfloat &);
    friend bigfloat operator+(const bigfloat &, const bigfloat &);
    friend bigfloat operator*(const bigfloat &, const bigfloat &);
    friend bigfloat operator/(const bigfloat &,const bigfloat &);

    bigfloat &operator-=(const bigfloat &);
    bigfloat &operator+=(const bigfloat &);
    bigfloat &operator*=(const bigfloat &);
    bigfloat &operator/=(const bigfloat &);

    const bigfloat &operator--();
    const bigfloat operator--(int);

    const bigfloat &operator++();
    const bigfloat operator++(int);


    friend bigfloat substract(const bigfloat &, lli);
    friend bigfloat add(const bigfloat &, lli);
    friend bigfloat multiply(const bigfloat &, lli);
    friend bigfloat divide(const bigfloat &, lli);


    friend bool operator==(const bigfloat &, const bigfloat &);
    friend bool operator==(lli, const bigfloat &);
    friend bool operator==(const bigfloat &, lli);



    friend std::strong_ordering operator<=>(const bigfloat &, const bigfloat &);
    friend std::strong_ordering operator<=>(lli, const bigfloat &);
    friend std::strong_ordering operator<=>(const bigfloat &, lli);
};

//bigfloat operator ""_bf(long double);

bigfloat operator ""_bf(unsigned long long);
#endif //VERY_LONG_FLOAT_BIGFLOAT_H
