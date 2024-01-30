#include "bigfloat.h"

#define BASE 1e9
#define CAPACITY 10

bigfloat::bigfloat() {
    _signum = false;
    _exponent = 1;
    _mantissa = {0};
    _precision = 0;
}

bigfloat::bigfloat(std::string input) {

    if (input[0] == '-'){
        _signum = true;
        input.erase(input.begin());
    }else{
        _signum = false;
    }

    char separator = input.find('.') < std::string::npos ? '.' : ',';

    _exponent = 0;
    _precision = 0;

    if (input[0] == '0'){
        input.erase(input.begin()); // delete the leading zero
        input.erase(input.begin()); // delete the sep

        while(input.front() == '0'){
            input.erase(input.begin());
            _exponent--;
            _precision++;
        }

    } else{
        _exponent = input.find(separator);
        input.erase(input.begin() + _exponent);
    }


    int accum = 0;
    int counter = 0;

    for(char digit : input){
        if (counter < CAPACITY){
            add_digit(accum, digit);
            counter++;
//            if (accum == 0){
//                _mantissa.push_back(accum);
//            }
        } else{
            _mantissa.push_back(accum);
            accum = to_digit(digit);
            counter = 1;
        }
        _precision++;
    }
    while(counter < CAPACITY){
        accum *= 10;
        counter++;
    }
    _mantissa.push_back(accum);
    discard_zeros();

}

void bigfloat::add_digit(int& x, char digit) {
    x = 10*x + to_digit(digit);
}

int bigfloat::to_digit(char digit) {
    return digit - '0';
}

std::string bigfloat::num2string(unsigned n) {
    std::ostringstream stm;
    stm << n << "{:010}";
    return stm.str();
//    std::formatter();
//format()
}

//int bigfloat::scale(int x) {
//    return ceil(log10(x + (x % 10 == 0)));
//}


std::string bigfloat::to_string() {
    std::string number;

    for (unsigned digits : _mantissa){
        number += num2string(digits);
    }

    if (_exponent > 0){
        number.insert(_exponent, ".");
    } else{
        number.insert(number.begin(), -_exponent, '0');
        number.insert(0, "0.");
    }


    if (_signum){
        return '-' + number + '0';
    }

    return number + '0';
}

void bigfloat::discard_zeros() {
    while (_mantissa.back() == 0){
        _mantissa.pop_back();
        _precision--;
    }
    while (_mantissa.back() % 10 == 0){
        _mantissa.back() /= 10;
        _precision--;
    }
}

bigfloat bigfloat::operator-() {
    _signum = !_signum;
    return *this;
}


//bigfloat bigfloat::operator+(bigfloat x) {
//    unsigned carry;
//
//    auto num_size = _mantissa.size();
//    auto x_size = x._mantissa.size();
//    if (_precision > x._precision){
//
//        for (auto i = num_size - 1; i >= x_size; --i){
////            if (x._precision +  )
//            x._mantissa.push_back(_mantissa[i + x._exponent - _exponent]);
//        }
//    }
//
//
//
//    for (auto i = x_size-1; i > 0; --i ){
//
//        auto exp = 1;
//        while(_mantissa[i] == 0 and exp < BASE){
//            i--;
//            exp*=10;
//        }
//
//        x._mantissa[i] += carry + (i + x._exponent - _exponent < num_size ? _mantissa[i + x._exponent - _exponent]*exp : 0);
//
//        if(x._mantissa[i] > BASE){
//            carry = x._mantissa[i] / BASE;
//            x._mantissa[i] %= BASE;
//            if (x._mantissa[i] == 0){
//                x._mantissa.insert(std::next(x._mantissa.begin(), i), 7, 0);
//            }
//        } else{
//            carry = 0;
//        }
//    }
//
//    x.discard_zeros();
//
//    for (auto i = x._exponent - _exponent - 1; i > 0; --i){
//
//        _mantissa[i] += carry;
//        if(_mantissa[i] > BASE){
//            carry = _mantissa[i] / BASE;
//            _mantissa[i] %= BASE;
//            if(_mantissa[i] == 0){
//                x._mantissa.insert(x._mantissa.begin(), 7, 0);
//            }
//        } else{
//            carry = 0;
//        }
//
//        x._mantissa.insert(x._mantissa.begin(), _mantissa[i]);
//    }
//    if (carry != 0)
//        x._mantissa.insert(x._mantissa.begin(), carry);
//
//    return x;
//}


///*n is the n-th digit of a whole number, and -n is the n-th digit of a float part
// * e.g. effectively it returns the coefficient at n-th power of 10 in factorisation*/
//int bigfloat::operator[](const int index) const{
//    if (index < 0){
//        if (_exponent < index){
//            return 0;
//        }
//        int float_index;
//        if (_exponent >= 0){
//            float_index = _exponent/CAPACITY
//            return _mantissa[_exponent + index]/
//        }
//
//    }
//}

std::strong_ordering bigfloat::operator<=>(bigfloat x) const {

    if (_signum != x._signum){
        return x._signum <=> _signum;
    }

    if (_exponent != x._exponent){
        return _exponent <=> x._exponent;
    }


    auto shared_size = fmin(_mantissa.size(), x._mantissa.size());
    for (int i = 0; i < shared_size; ++i){
        if (_mantissa[i] != x._mantissa[i]){
            return _mantissa[i] <=> x._mantissa[i];
        }
    }
    return _mantissa.size() <=> x._mantissa.size();

}

bool bigfloat::operator==(bigfloat x) const {
    if (_signum != x._signum || _exponent != x._exponent){
        return false;
    }


    auto shared_size = fmin(_mantissa.size(), x._mantissa.size());
    for (int i = 0; i < shared_size; ++i){
        if (_mantissa[i] != x._mantissa[i]){
            return false;
        }
    }
    return _mantissa.size() == x._mantissa.size();
}




