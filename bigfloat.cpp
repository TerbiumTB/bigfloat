#include "bigfloat.h"

#include <utility>


// static-------------------------------
lli bigfloat::_precision = 100;

lli bigfloat::precision() {
    return _precision;
}

lli bigfloat::precision(lli p) {
    if (p >= 0) {
        _precision = p;
    }
    return _precision;
}

digit_t bigfloat::to_digit(char digit) {
    return digit - '0';
}

void bigfloat::add_digit(digit_t &x, char digit) {
    x = 10 * x + to_digit(digit);
}

std::string bigfloat::num2string(digit_t n) {
    std::ostringstream stm;
    stm << n;
    return stm.str();
}

std::string bigfloat::fnum2string(digit_t n) {
    std::ostringstream stm;
    stm << n;
    std::string format(CAPACITY > stm.str().length() ? CAPACITY - stm.str().length() : 0, '0');
    return format + stm.str();
}
//-------------------------------


//constructors-------------------------------
bigfloat::bigfloat() {
    _signum = false;
    _exponent = 0;
//    _mantissa.push_back(0);
}

bigfloat::bigfloat(std::string input) {

    if (input[0] == '-') {
        _signum = true;
        input.erase(input.begin());
    } else {
        _signum = false;
    }


    char separator = '.';

    if (input.find('.') == std::string::npos) {
        if (input.find(',') < std::string::npos) separator = ',';
        else input += '.';
    }

//    char separator = input.find('.') < std::string::npos ? '.' : ',';


    input = input + std::string(mod(input.size() - input.find(separator) - 1, CAPACITY), '0');

    input = std::string(mod(input.size() - 1, CAPACITY), '0') + input;

    _exponent = (lli) input.find(separator) / CAPACITY;
    std::erase(input, separator);

    digit_t accum = 0;
    auto iter = input.begin();
    while (iter != input.end()) {
        for (int i = 0; i < CAPACITY; ++i) {
            add_digit(accum, *iter);
            iter++;
        }
        _mantissa.push_back(accum);
        accum = 0;
    }

    discard_zeros();

}

bigfloat operator ""_bf(long double number) {
    if (number == 0.0)
        return {};
    return {std::to_string(number)};
}

bigfloat operator ""_bf(unsigned long long number) {
    if (number == 0)
        return {};
    return {std::to_string(number) + '.'};
}
//-------------------------------


//properties-------------------------------
int bigfloat::sign() const {
    return _signum ? -1 : 1;
}

lli bigfloat::greatest() const {
    return _exponent - 1;
}

lli bigfloat::lowest() const {
    return _exponent - (lli) _mantissa.size();
}
//-------------------------------


//-------------------------------
std::string bigfloat::to_string() {
    std::string number = _signum ? "-" : "";

    for (auto i = 0; i < _mantissa.size(); ++i) {
        if (i == _exponent) number += '.';

        if (i == 0) number += num2string(_mantissa[i]);
//        if(i == ){
//
//        }
        else
            number += fnum2string(_mantissa[i]);
    }


    if (_mantissa.size() == _exponent) number += ".";

    while (number.back() == '0')
        number.pop_back();


    return number + '0';
}
//-------------------------------


void bigfloat::discard_zeros() {
    while (_mantissa.size() != _exponent && _mantissa.back() == 0)
        _mantissa.pop_back();

    while (_exponent != 1 && _mantissa.front() == 0) {
        _mantissa.erase(_mantissa.begin());
        --_exponent;
    }
}


//comparants-------------------------------
std::strong_ordering operator<=>(const bigfloat &x, const bigfloat &y) {

    if (y._signum != x._signum) return x._signum <=> y._signum;

    if (y._exponent != x._exponent) return x._exponent <=> y._exponent;

    for (lli index = x._exponent - 1; index >= x._exponent - (lli) x._mantissa.size(); --index)
        if (x[index] != y[index]) return x[index] <=> y[index];


    return y._mantissa.size() <=> x._mantissa.size();

}

std::strong_ordering operator<=>(lli x, const bigfloat &y) {

    if (y.sign() * x < 0) return x <=> y.sign();

    x = abs(x);

    if (y.greatest() != 0) return 0 <=> y.greatest();

    if (y[0] != (digit_t) x) return (digit_t) x <=> y[0];

    for (auto i = -1; i >= y.lowest(); --i)
        if (y[i]) return 0 <=> y.sign();


    return 0 <=> 0;
}

std::strong_ordering operator<=>(const bigfloat &x, lli y) {
    \

    if (x.sign() * y < 0) return x.sign() <=> y;

    y = abs(y);

    if (x.greatest() != 0) return x.greatest() <=> 0;

    if (x[0] != (digit_t) y) return x[0] <=> (digit_t) y;

    for (auto i = -1; i >= x.lowest(); --i)
        if (x[i]) return x.sign() <=> y;


    return 0 <=> 0;
}

bool operator==(const bigfloat &x, const bigfloat &y) {
    if (y._signum != x._signum || y._exponent != x._exponent || x._mantissa.size() != y._mantissa.size()) return false;

    for (lli index = x._exponent - (lli) x._mantissa.size(); index < x._exponent; ++index)
        if (x[index] != y[index]) return false;

    return true;
}

bool operator==(lli x, const bigfloat &y) {
    return (x * y.sign() >= 0) && y._mantissa.size() == 1 && y.greatest() == 0 && abs(x) == y[0];
}

bool operator==(const bigfloat &x, lli y) {
    return y == x;
}
//-------------------------------


//-------------------------------
/*basically it returns the n-th digit in current base (BASE),
 * so, for example, in BASE = 4, for x = 12.3 -> {1, 2, 3}
 * x[0] = 2, x[1] = 1, x[-1] = 3, x[123] = 0
 * */
digit_t bigfloat::operator[](lli index) const {
    if (index < _exponent && index <= greatest()) return _mantissa[_exponent - index - 1];
    return 0;
}

inline constexpr digit_t &bigfloat::operator[](lli index) {
    if (index > greatest()) {
        _mantissa.insert(_mantissa.begin(), index - greatest(), 0);
        return _mantissa[++_exponent - index - 1];
    } else if (index < lowest()) {
        _mantissa.insert(_mantissa.end(), lowest() - index, 0);
    }

    return _mantissa[_exponent - index - 1];
}
//-------------------------------


//subtraction-------------------------------
bigfloat bigfloat::operator-() const {
    auto inverse(*this);
    inverse._signum = !_signum;
    return inverse;
}

bigfloat operator-(bigfloat a, const bigfloat &b) {

    if (b._signum) return a + (-b);
    else if (a._signum) return -(-a + b);
    else if (a < b) return -(b - a);

    for (auto i = (lli) fmin(a.lowest(), b.lowest()); i <= (lli) fmax(a.greatest(), b.greatest()); ++i) {
        if (a[i] < b[i]) {
            a[i] += (BASE - b[i]);
            for (auto j = i + 1; j <= a.greatest(); ++j) {
                if (a[j] == 0) {
                    a[j] = BASE - 1;
                } else {
                    a[j]--;
                    break;
                }
            }
        } else {
            a[i] -= b[i];
        }
    }

    a.discard_zeros();

    return a;
}

bigfloat &bigfloat::operator-=(const bigfloat &other) {
    return *this = *this - other;
}

bigfloat operator-(bigfloat a, lli b) {
    if (b < 0) return a + (-b);
    else if (a._signum) return -(-a + b);
    else if (a < b) return -(b - a);


    if (a[0] == 0 || a[0] - b < 0) {
        a[0] += BASE - b;
        for (auto j = 1; j <= a.greatest(); ++j) {
            if (a[j] == 0) {
                a[j] = BASE - 1;
            } else {
                a[j]--;
                break;
            }
        }
    } else {
        a[0] -= b;
    }

    a.discard_zeros();

    return a;
}

bigfloat operator-(lli a, bigfloat b) {
    return -(std::move(b) - a);
}

bigfloat &bigfloat::operator-=(lli b) {
    return *this = *this - b;
}

const bigfloat &bigfloat::operator--() {
    return *this -= 1;
}

const bigfloat bigfloat::operator--(int) {
    *this -= 1;
    return (*this + 1);
}
//-------------------------------


//addition-------------------------------
bigfloat operator+(bigfloat a, const bigfloat &b) {
    if (a._signum != b._signum) {
        if (b._signum) return a - (-b);
        return b - (-a);
    }

    auto carry = 0;
    for (auto i = (lli) fmin(a.lowest(), b.lowest()); i <= (lli) fmax(a.greatest(), b.greatest()) || carry != 0; ++i) {
        a[i] += b[i] + carry;
        if (a[i] >= BASE) {
            a[i] -= BASE;
            carry = 1;
        } else {
            carry = 0;
        }
    }

    a.discard_zeros();

    return a;
}

bigfloat &bigfloat::operator+=(const bigfloat &other) {
    return *this = *this + other;
}

bigfloat operator+(bigfloat a, lli b) {
    if (a.sign() * b < 0) {
        if (b < 0) return a - (-b);
        return b - (-a);
    }

    a[0] += b;
    if (a[0] >= BASE) {
        a[0] -= BASE;
        a[1]++;
    }

    a.discard_zeros();

    return a;
}

bigfloat operator+(lli a, bigfloat b) {
    return std::move(b) + a;
}

bigfloat &bigfloat::operator+=(lli b) {
    return *this = *this + b;
}

const bigfloat &bigfloat::operator++() {
    return *this += 1;
}

const bigfloat bigfloat::operator++(int) {
    *this += 1;
    return (*this - 1);
}
//-------------------------------

//multiplication-------------------------------
bigfloat operator*(bigfloat a, const bigfloat &b) {
    if (a == 0_bf || b == 0_bf) return 0_bf;

    digit_t carry;
    auto c = 0_bf;

    for (auto i = (lli) fmin(a.lowest(), b.lowest()); i <= a.greatest(); ++i) {
        carry = 0;

        for (auto j = (lli) fmin(a.lowest(), b.lowest()); j <= b.greatest() || carry != 0; ++j) {
            auto x = c[i + j] + a[i] * b[j] + carry;

            if (bigfloat::valuable(i + j)) c[i + j] = x % BASE;

            carry = x / BASE;
        }
    }

    c.discard_zeros();

    c._signum = a._signum != b._signum;
    c._exponent = (lli) c._mantissa.size() - (lli) fmin(a.accuracy() + b.accuracy(), bigfloat::border());

    return c;
}

bigfloat &bigfloat::operator*=(const bigfloat &b) {
    return *this = (*this) * b;
}

bigfloat operator*(bigfloat a, lli b) {
    if (a == 0_bf || b == 0) return 0_bf;

    if (b < 0) {
        a._signum = !a._signum;
        b = -b;
    }
    digit_t carry = 0;

    for (auto i = a.lowest(); i <= a.greatest() || carry != 0; ++i) {
        auto x = (a[i] * b + carry);
        a[i] = x % BASE;
        carry = x / BASE;
    }

    a.discard_zeros();

    return a;
}

bigfloat operator*(lli a, bigfloat b) {
    return std::move(b) * a;
}

bigfloat &bigfloat::operator*=(lli b) {
    return *this = (*this) * b;
}

lli bigfloat::accuracy() const {
    return (lli) _mantissa.size() - _exponent;
}

bool bigfloat::valuable(lli index) {
    return index >= 0 or (-index <= border());
}

lli bigfloat::border() {
//    return (bigfloat::precision()/CAPACITY) + ((bigfloat::precision()%CAPACITY)!=0);
    return -(bigfloat::precision() / CAPACITY) + 1;
}
//-------------------------------


//division-------------------------------
bigfloat operator/(bigfloat a, lli b) {
    if (b == 0) throw std::overflow_error("division by 0");

    for (auto i = a.greatest(); i >= a.lowest() && a[i] != 0 && i >= a.border(); --i) {
        a[i - 1] += (a[i] % b) * BASE;
        a[i] /= b;
    }

    return a;
}

bigfloat &bigfloat::operator/=(lli b) {
    return *this = *this / b;
}

bigfloat operator/(bigfloat a, bigfloat b){
    if (b == 0) throw std::overflow_error("division by 0");

    bigfloat c{};

    c._signum = (a._signum != b._signum);
    a._signum = b._signum = false;

    if (a < b) c._mantissa.insert(c._mantissa.end(), a._exponent - b._exponent + 1, 0);

    c._exponent = a._exponent - b._exponent + 1;


    if (b._mantissa[0] == 0) b._mantissa.erase(b._mantissa.begin());

    if (a._mantissa[0] == 0) a._mantissa.erase(a._mantissa.begin());

    a._exponent = b._exponent;

    while(c.lowest() >= c.border() && a != 0){

        if (a < b) a._exponent++;

        digit_t floor, ceil;
        if (a._exponent > b._exponent){
            floor = a._mantissa[0] * BASE / (b._mantissa[0] + 1);
            ceil = (a._mantissa[0]+1) * BASE / (b._mantissa[0]);
        } else{
            floor = a._mantissa[0] / (b._mantissa[0] + 1);
            ceil = a._mantissa[0] / (b._mantissa[0]);
        }


        while(b * floor <= a && floor < ceil) {
            if (b*((floor + ceil) / 2 + (floor + ceil) % 2) <= a){
                floor = (floor + ceil) / 2 + (floor + ceil) % 2;
            } else{
                ceil = (floor + ceil) / 2;
            }

        }

        c._mantissa.push_back(floor);
        a -= b * floor;
        a.discard_zeros();
    }

    c.discard_zeros();


    return c;

}