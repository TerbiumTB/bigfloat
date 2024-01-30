#include "bigfloat.h"

// static-------------------------------
digit_t bigfloat::to_digit(char digit) {
    return digit - '0';
}

void bigfloat::add_digit(digit_t & x, char digit) {
    x = 10*x + to_digit(digit);
}

std::string bigfloat::num2string(digit_t n) {
    std::ostringstream stm;
    stm << n;
    return stm.str();
}

std::string bigfloat::fnum2string(digit_t n) {
    std::ostringstream stm;
    stm << n;
    std::string format(CAPACITY - stm.str().length(), '0');
    return format + stm.str();
}
//-------------------------------


//constructors-------------------------------
bigfloat::bigfloat() {
    _signum = false;
    _exponent = 0;
    _mantissa = {0};
}

bigfloat::bigfloat(std::string input) {

    if (input[0] == '-'){
        _signum = true;
        input.erase(input.begin());
    }else{
        _signum = false;
    }

    char separator = input.find('.') < std::string::npos ? '.' : ',';

    input = input + std::string(mod(input.size() - input.find(separator) - 1, CAPACITY), '0');

    input = std::string(mod(input.size() - 1, CAPACITY), '0') + input;

    _exponent = (lli) input.find(separator)/CAPACITY;
    std::erase(input, separator);

    digit_t accum = 0;
    auto iter = input.begin();
    while (iter != input.end()){
        for(int i = 0; i < CAPACITY; ++i){
            add_digit(accum, *iter);
            iter++;
        }
        _mantissa.push_back(accum);
        accum = 0;
    }
    discard_zeros();

}

bigfloat operator ""_bf(long double number) {
    return {std::to_string(number)};
}

bigfloat operator ""_bf(unsigned long long number) {
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

lli bigfloat::lowest() {
    return _exponent - (lli) _mantissa.size();
}
//-------------------------------


//-------------------------------
std::string bigfloat::to_string() {
    std::string number = _signum ? "-" : "";

    for (auto i = 0; i < _mantissa.size(); ++i){
        if (i == _exponent)
            number += '.';

        if (i == 0){
            number += num2string(_mantissa[i]);
        }
        else{
            number += fnum2string(_mantissa[i]);
        }
    }

    number += '0';
    while(number.back() == '0'){
        number.pop_back();
    }

    return number + '0';
}
//-------------------------------


void bigfloat::discard_zeros() {
    while (_mantissa.back() == 0){
        _mantissa.pop_back();
    }
}


//comparants-------------------------------
std::strong_ordering operator<=>(const bigfloat& x, const bigfloat& y) {

    if (y._signum != x._signum){
        return x._signum <=> y._signum;
    }

    if (y._exponent != x._exponent){
        return x._exponent <=> y._exponent;
    }

    for(lli index = x._exponent - 1; index >=  x._exponent - (lli) x._mantissa.size(); --index){
        if(x[index] != y[index]){
            return x[index] <=> y[index];
        }
    }

    return y._mantissa.size() <=> x._mantissa.size();

}

bool operator==(const bigfloat& x, const bigfloat& y){
    if (y._signum != x._signum || y._exponent != x._exponent || x._mantissa.size() != y._mantissa.size()){
        return false;
    }

    for(lli index = x._exponent - (lli) x._mantissa.size(); index < x._exponent; ++index){
        if(x[index] != y[index]){
            return false;
        }
    }
    return true;
}
//-------------------------------


//-------------------------------
/*basically it returns the n-th digit in base BASE,
 * so for example BASE = 4, x = 12.3 -> {1, 2, 3}
 * x[0] = 2, x[1] = 1, x[-1] = 3, x[123]=0
 * */
digit_t bigfloat::operator[](lli index) const {
    if (index < _exponent && index <= greatest()){
        return _mantissa[_exponent - index - 1];
    }
    return 0;
}

inline constexpr digit_t &bigfloat::operator[](lli index) {
    if (index > greatest()){
        _mantissa.insert(_mantissa.begin(),  index - greatest(), 0);
        return _mantissa[++_exponent - index -1];
    } else if (index < lowest()){
        _mantissa.insert(_mantissa.end(),  lowest() - index, 0);
    }

    return _mantissa[_exponent - index - 1];
}
//-------------------------------


//subtraction-------------------------------
bigfloat bigfloat::operator-() {
    _signum = !_signum;
    return *this;
}

bigfloat operator-(bigfloat a, bigfloat b){
    for (auto i = (lli) fmin(a.lowest(), b.lowest()); i <= (lli) fmax(a.greatest(), b.greatest()); ++i){
        if (a[i] < b[i]){
            a[i] += (BASE - b[i]);
            a[i+1]--;
        } else{
            a[i] -= b[i];
        }
    }

    return a;
}

bigfloat& bigfloat::operator-=(bigfloat other) {
    return *this = *this - std::move(other);

}

const bigfloat& bigfloat::operator--() {
    return *this -= 1_bf;
}

const bigfloat bigfloat::operator--(int) {
    *this -= 1_bf;
    return (*this + 1_bf);
}
//-------------------------------


//addition-------------------------------
bigfloat operator+(bigfloat a, bigfloat b){
    if (a._signum != b._signum){
        if (b._signum) return a - (-b);
        return b - (-a);
    }

    for (auto i = (lli) fmin(a.lowest(), b.lowest()); i <= (lli) fmax(a.greatest(), b.greatest()); ++i){
        a[i] += b[i];
        if (a[i] > BASE){
            a[i] -= BASE;
            b[i+1]++;
        }
    }
    return a;
}

bigfloat& bigfloat::operator+=(bigfloat other) {
    return *this = *this + std::move(other);
}

const bigfloat& bigfloat::operator++() {
    return *this += 1_bf;
}

const bigfloat bigfloat::operator++(int) {
    *this += 1_bf;
    return (*this - 1_bf);
}
//-------------------------------