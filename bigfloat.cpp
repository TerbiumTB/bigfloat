#include "bigfloat.h"


bigfloat::bigfloat() {
    _sign = false;
    _exponent = 1;
    _mantissa = {0};
}
bigfloat::bigfloat(std::string &input) {
    if (input[0] == '-'){
        _sign = true;
        input.erase(input.begin());
    }else{
        _sign = false;
    }
}