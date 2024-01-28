#include "bigfloat.h"


bigfloat::bigfloat() {
    _sign = false;
    _exponent = 1;
    _mantissa = {0};
}

bigfloat::bigfloat(std::string input) {

    if (input[0] == '-'){
        _sign = true;
        input.erase(input.begin());
    }else{
        _sign = false;
    }

    char separator = input.find('.') < std::string::npos ? '.' : ',';
    bool float_part = false;

    if (input[0] == '0'){
        input.erase(input.begin());//delete the leading zero
        input.erase(input.begin());//delete the sep

        while(input.front() == '0'){
            input.erase(input.begin());
            _exponent--;
        }

        float_part = true;
    }


    int accum = 0;
    int exp = 0;

    for(char digit : input){
        if (!float_part){
            if (digit == separator){
                float_part = true;
                continue;
            } else{
                _exponent++;
            }
        }

        if (exp < 9){
            add_digit(accum, digit);
            if (accum == 0){
                _mantissa.push_back(accum);
            } else{
                exp++;
            }
        } else{
            _mantissa.push_back(accum);
            accum = toDigit(digit);
            exp = 1;
        }
    }
    _mantissa.push_back(accum);

}

void bigfloat::add_digit(int& x, char digit) {
    x = 10*x + toDigit(digit);
}

int bigfloat::toDigit(char digit) {
    return digit - '0';
}

std::string bigfloat::num2string(unsigned n) {
    std::ostringstream stm;
    stm << n;
    return stm.str();
}
std::string bigfloat::toString() {
    std::string number;

//
//    if (_sign){
//        number += '-';
//    }

    for (unsigned digits : _mantissa){
        number += num2string(digits);
    }

    if (_exponent > 0){
        number.insert(_exponent, ".");
    } else{
        number.insert(number.begin(), -_exponent, '0');
        number.insert(0, "0.");
    }


    if (_sign){
        return '-' + number + '0';
    }

    return number + '0';
}



