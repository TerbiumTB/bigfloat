#include "bigfloat.h"



bigfloat::bigfloat() {
    _signum = false;
    _integer = {0};
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

    _exponent = input.find(separator)/CAPACITY;
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

int bigfloat::sign() {
    return _signum ? -1 : 1;
}

//int bigfloat::greatest() {
//    return
//}
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

void bigfloat::discard_zeros() {
    while (_mantissa.back() == 0){
        _mantissa.pop_back();
    }
}
//
//bigfloat bigfloat::operator-() {
//    _signum = !_signum;
//    return *this;
//}
//
//
//bigfloat bigfloat::operator+(bigfloat x) {
//    char carry = 0;
//
//    auto num_size = _mantissa.size();
//    auto x_size = x._mantissa.size();
//
//    for (auto i = x_size - x._exponent + _exponent; i < num_size ; ++i){
//        x._mantissa.push_back(_mantissa[i]);
//    }
//
//
//
//    for (auto i = x_size - 1; i > 0; --i ){
//
//        x._mantissa[i] += carry + (i - x._exponent + _exponent < num_size ? _mantissa[i - x._exponent + _exponent] : 0);
//
//        if(x._mantissa[i] > 9){
//            carry = 1;
//            x._mantissa[i] -= 10;
//        } else{
//            carry = 0;
//        }
//    }
//
//    x.discard_zeros();
//
//    for (auto i = -x._exponent + _exponent; i > 0; --i){
//
//        _mantissa[i] += carry;
//        if(_mantissa[i] + carry > 9){
//            x._mantissa.insert(x._mantissa.begin(), _mantissa[i]);
//        } else{
//            x._mantissa.insert(x._mantissa.begin(), _mantissa[i] + carry);
//            carry = 0;
//        }
//
//
//    }
//
//    if (carry != 0)
//        x._mantissa.insert(x._mantissa.begin(), carry);
//
//    x._exponent = fmax(_exponent, x._exponent);
//
//    return x;
//}
//
//
//
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

//    auto shared_size = fmin(_mantissa.size(), x._mantissa.size());
//    for (int i = 0; i < shared_size; ++i){
//        if (_mantissa[i] != x._mantissa[i]){
//            return false;
//        }
//    }
//    return _mantissa.size() == x._mantissa.size();
}

digit_t bigfloat::operator[](lli index) const {
    if (0 < _exponent - index && _exponent - index <= _mantissa.size()){
        return _mantissa[_exponent - index - 1];
    }
    return 0;
}