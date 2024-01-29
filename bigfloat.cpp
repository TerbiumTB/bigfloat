#include "bigfloat.h"

#define CAPACITY 100000000
#define CAPACITY_LEN 8

bigfloat::bigfloat() {
    _signum = false;
    _exponent = 1;
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

    _exponent = 0;

    if (input[0] == '0'){
        input.erase(input.begin()); // delete the leading zero
        input.erase(input.begin()); // delete the sep

        while(input.front() == '0'){
            input.erase(input.begin());
            _exponent--;
        }

    } else{
        _exponent = input.find(separator);
        input.erase(input.begin() + _exponent);
    }


    for(char digit : input){
        _mantissa.push_back(to_digit(digit));
    }

    discard_zeros();
}

char bigfloat::to_digit(char digit) {
    return digit - '0';
}

std::string bigfloat::to_string() {
    std::string number;

    for (char digit : _mantissa){
        number += digit + '0';
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
    }
}

bigfloat bigfloat::operator-() {
    _signum = !_signum;
    return *this;
}


bigfloat bigfloat::operator+(bigfloat x) {
    char carry = 0;

    auto num_size = _mantissa.size();
    auto x_size = x._mantissa.size();

    for (auto i = x_size - x._exponent + _exponent; i < num_size ; ++i){
        x._mantissa.push_back(_mantissa[i]);
    }



    for (auto i = x_size - 1; i > 0; --i ){

        x._mantissa[i] += carry + (i - x._exponent + _exponent < num_size ? _mantissa[i - x._exponent + _exponent] : 0);

        if(x._mantissa[i] > 9){
            carry = 1;
            x._mantissa[i] -= 10;
        } else{
            carry = 0;
        }
    }

    x.discard_zeros();

    for (auto i = -x._exponent + _exponent; i > 0; --i){

        _mantissa[i] += carry;
        if(_mantissa[i] + carry > 9){
            x._mantissa.insert(x._mantissa.begin(), _mantissa[i]);
        } else{
            x._mantissa.insert(x._mantissa.begin(), _mantissa[i] + carry);
            carry = 0;
        }


    }

    if (carry != 0)
        x._mantissa.insert(x._mantissa.begin(), carry);

    x._exponent = fmax(_exponent, x._exponent);

    return x;
}



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