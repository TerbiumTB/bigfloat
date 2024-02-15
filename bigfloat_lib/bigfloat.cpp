#include "bigfloat.h"

#include <utility>
#include <iostream>
#include <cmath>
#include <compare>

namespace Bigfloat {
// static-------------------------------
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
        _exponent = 1;
        _precision = 100;
        _mantissa.push_back(0);
    }

    bigfloat::bigfloat(lli input) {
        _precision = 100;
        _exponent = 0;

        _signum = false;

        if (input < 0) {
            _signum = true;
            input = -input;
        }

        while (input > 0) {
            _mantissa.insert(_mantissa.begin(), input % BASE);
            input /= BASE;

            _exponent++;
        }
    }

    bigfloat::bigfloat(lli input, lli precision) {
        _precision = precision;
        _exponent = 0;

        _signum = false;

        if (input < 0) {
            _signum = true;
            input = -input;
        }

        while (input > 0) {
            _mantissa.insert(_mantissa.begin(), input % BASE);
            input /= BASE;

            _exponent++;
        }
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

        _precision = static_cast<lli>(fmax(100, _mantissa.size() - _exponent));

    }

    bigfloat operator ""_bf(long double number) {
        if (number == 0.0)
            return {};
        return bigfloat{std::to_string(number)};
    }

    bigfloat operator ""_bf(unsigned long long number) {
        if (number == 0)
            return {};
        return bigfloat(number);
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

    lli &bigfloat::precision() {
        return _precision;
    }

    lli bigfloat::border() const {
        return -(_precision / CAPACITY + ((_precision % CAPACITY) != 0));
    }
//-------------------------------


//-------------------------------
    std::string bigfloat::to_string() const {
        std::string number = _signum ? "-" : "";

        for (auto i = 0; i < _mantissa.size(); ++i) {

            if (i == 0) {
                number += num2string(_mantissa[i]);
                continue;
            }

            if (i == _exponent) number += '.';

            number += fnum2string(_mantissa[i]);
        }


        if (_mantissa.size() == _exponent) {
            return number + ".0";
        }

        while (number.back() == '0')
            number.pop_back();


        return number;
    }

    std::string bigfloat::to_string(lli precision) const {
        std::string number = _signum ? "-" : "";

        auto extra = precision % CAPACITY;

        for (auto i = 0; i < _mantissa.size(); ++i) {

            if (i == 0) {
                number += num2string(_mantissa[i]);
                continue;
            }

            if (i == _exponent) number += '.';


            if (i >= _exponent && i == _exponent + precision / CAPACITY - (extra == 0)) {
                if (extra != 0) {
                    number += fnum2string(_mantissa[i]).substr(0, extra);
                } else {
                    number += fnum2string(_mantissa[i]);
                }
                break;
            }

            number += fnum2string(_mantissa[i]);
        }


        if (_mantissa.size() == _exponent) {
            return number + ".0";
        }


        return number;
    }

    std::ostream &operator<<(std::ostream &os, const bigfloat &number) {
        return os << number.to_string();
    }
//-------------------------------


    void bigfloat::discard_zeros() {
        while (_mantissa.size() != _exponent && _mantissa.back() == 0)
            _mantissa.pop_back();

        while (_exponent > 1 && _mantissa.front() == 0) {
            _mantissa.erase(_mantissa.begin());
            --_exponent;
        }
    }


//comparants-------------------------------
    std::strong_ordering operator<=>(const bigfloat &x, const bigfloat &y) {

        if (y._signum != x._signum) return x._signum <=> y._signum;

        if (x._signum) return -y <=> -x;

        if (y._exponent != x._exponent) return x._exponent <=> y._exponent;

        for (lli index = x._exponent - 1; index >= x._exponent - (lli) x._mantissa.size(); --index)
            if (x[index] != y[index]) return x[index] <=> y[index];


        return y._mantissa.size() <=> x._mantissa.size();

    }

    std::strong_ordering operator<=>(lli x, const bigfloat &y) {

        if (y.sign() * x < 0) return x <=> y.sign();

        if (x < 0) return (-y <=> -x);

        if (y.greatest() != 0) return 0 <=> y.greatest();

        if (y[0] != (digit_t) x) return (digit_t) x <=> y[0];

        for (auto i = -1; i >= y.lowest(); --i)
            if (y[i]) return 0 <=> y[i];


        return 0 <=> 0;
    }

    std::strong_ordering operator<=>(const bigfloat &x, lli y) {


        if (x.sign() * y < 0) return x.sign() <=> y;

//        y = abs(y);
        if (y < 0) return -y <=> -x;

        if (x.greatest() != 0) return x.greatest() <=> 0;

        if (x[0] != (digit_t) y) return x[0] <=> (digit_t) y;

        for (auto i = -1; i >= x.lowest(); --i)
            if (x[i]) return x[i] <=> 0;


        return 0 <=> 0;
    }

    bool operator==(const bigfloat &x, const bigfloat &y) {
        if (x == 0 && y == 0) return true;

        if (y._signum != x._signum || y._exponent != x._exponent || x._mantissa.size() != y._mantissa.size())
            return false;

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
        if (lowest() <= index && index <= greatest()) return _mantissa[_exponent - index - 1];
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

    bigfloat operator-(const bigfloat &x, const bigfloat &y) {


        if (y._signum) return x + (-y);
        else if (x._signum) return -(-x + y);
        else if (x < y) return -(y - x);

        auto c(x);
        c._precision = fmax(x._precision, y._precision);

        auto carry = 0;
        for (auto i = (lli) fmin(x.lowest(), y.lowest());
             i <= (lli) fmax(x.greatest(), y.greatest()) || carry != 0; ++i) {
            if (c[i] < y[i] + carry) {
                c[i] += (BASE - y[i] - carry);
                carry = 1;
            } else {
                c[i] -= (y[i] + carry);
                carry = 0;
            }
        }

        c.discard_zeros();

        return c;
    }

    bigfloat &bigfloat::operator-=(const bigfloat &other) {
        return *this = *this - other;
    }

    const bigfloat &bigfloat::operator--() {
        return *this = *this - 1_bf;
    }

    const bigfloat bigfloat::operator--(int) {
        *this -= 1_bf;
        return *this + 1_bf;
    }
//-------------------------------


//addition-------------------------------
    bigfloat operator+(const bigfloat &x, const bigfloat &y) {
        if (x._signum != y._signum) {
            if (y._signum) return x - (-y);
            return y - (-x);
        }

        auto c{x};
        c._precision = fmax(x._precision, y._precision);

        auto carry = 0;
        for (auto i = (lli) fmin(x.lowest(), y.lowest());
             i <= (lli) fmax(x.greatest(), y.greatest()) || carry != 0; ++i) {
            c[i] += y[i] + carry;
            if (c[i] >= BASE) {
                c[i] -= BASE;
                carry = 1;
            } else {
                carry = 0;
            }

        }

        c.discard_zeros();

        return c;
    }

    bigfloat &bigfloat::operator+=(const bigfloat &other) {
        return *this = *this + other;
    }

    const bigfloat &bigfloat::operator++() {
        return *this = *this + 1_bf;
    }

    const bigfloat bigfloat::operator++(int) {
        *this += 1_bf;
        return *this - 1_bf;
    }
//-------------------------------

//multiplication-------------------------------
    bigfloat operator*(const bigfloat &x, const bigfloat &y) {
        if (x == 0_bf || y == 0_bf) return 0_bf;

        digit_t carry;
        auto c = 0_bf;
        c._precision = x._precision + y._precision;

        for (auto i = (lli) fmin(x.lowest(), y.lowest()); i <= x.greatest(); ++i) {
            carry = 0;
            for (auto j = (lli) fmin(x.lowest(), y.lowest()); j <= y.greatest() || carry != 0; ++j) {
                auto m = c[i + j] + x[i] * y[j] + carry;

                c[i + j] = m % BASE;

                carry = m / BASE;
            }
        }

        c.discard_zeros();

        c._signum = x._signum != y._signum;
        if (c[0] == 0) {
            c._exponent = 1;
        } else {
            c._exponent = static_cast<lli>(c._mantissa.size()) + x.lowest() + y.lowest();
        }


        return c;
    }

    bigfloat &bigfloat::operator*=(const bigfloat &other) {
        return *this = (*this) * other;
    }

    bigfloat multiply(const bigfloat &x, lli n) {

        if (x == 0 || n == 0) return 0_bf;

        auto c{x};

        if (n < 0) {
            c._signum = !x._signum;
            n = -n;
        }
        digit_t carry = 0;

        for (auto i = x.lowest(); i <= x.greatest() || carry != 0; ++i) {
            auto m = (x[i] * n + carry);
            c[i] = m % BASE;
            carry = m / BASE;
        }

        c.discard_zeros();

        return c;
    }
//-------------------------------


//division-------------------------------
    bigfloat divide(const bigfloat &x, lli n) {
        if (n == 0) throw std::overflow_error("division by 0");

        auto c{x};

        for (auto i = c.greatest(); i >= 0 || i >= c.border(); --i) {
            c[i - 1] += (c[i] % n) * BASE;
            c[i] /= n;
        }
        c[c.border() - 1] += (c[c.border()] % n) * BASE;
        c[c.border()] /= n;

        c.discard_zeros();

        return c;
    }


    bigfloat operator/(const bigfloat &x, const bigfloat &y) {
        auto a{x}, b{y};

        if (b == 0) throw std::overflow_error("division by 0");

        bigfloat c{};

        c._signum = (a._signum != b._signum);
        a._signum = b._signum = false;

        c.precision() = fmax(a.precision(), b.precision());

        while (a._mantissa[0] == 0 && b._mantissa[0] == 0) {
            a._mantissa.erase(a._mantissa.begin());
            b._mantissa.erase(b._mantissa.begin());
        }

        if (a._mantissa[0] == 0) {
            while (a._mantissa[0] == 0) {
                a._mantissa.erase(a._mantissa.begin());
                c._mantissa.push_back(0);
            }
            c._exponent = 1;
        } else if (b._mantissa[0] == 0) {
            while (b._mantissa[0] == 0) {
                b._mantissa.erase(b._mantissa.begin());
                c._exponent++;
            }
            c._exponent += a._exponent;
        } else {
            c._mantissa.pop_back();
            c._exponent = a._exponent - b._exponent + 1;
        }

        if (a < b) c._mantissa.insert(c._mantissa.end(), a._exponent - b._exponent + 1, 0);

        a._exponent = b._exponent;

        while (c.lowest() + c.precision() >= 0 && a != 0) {

            if (a < b) a._exponent++;

            digit_t floor, ceil;
            if (a._exponent > b._exponent) {
                floor = a._mantissa[0] * BASE / (b._mantissa[0] + 1);
                ceil = ((a._mantissa[0] + 1) * BASE / (b._mantissa[0])) + 1;
            } else {
                floor = a._mantissa[0] / (b._mantissa[0] + 1);
                ceil = (a._mantissa[0] / (b._mantissa[0])) + 1;
            }


            while (multiply(b, floor) <= a && floor < ceil) {
                if (multiply(b, ((floor + ceil) / 2 + (floor + ceil) % 2)) <= a) {
                    floor = (floor + ceil) / 2 + (floor + ceil) % 2;
                } else {
                    ceil = (floor + ceil) / 2;
                }

            }

            c._mantissa.push_back(floor);
            a -= multiply(b, floor);
            a.discard_zeros();
        }
        if (c._mantissa.size() < c._exponent) {
            c._mantissa.insert(c._mantissa.end(), c._exponent - c._mantissa.size(), 0);
        }
        c.discard_zeros();

        return c;
    }

    bigfloat &bigfloat::operator/=(const bigfloat &other) {
        return *this = (*this) / other;
    }
}