#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "bigfloat.h"


int main() {
    std::string b = "-123";
    auto a = new bigfloat(b);
    std::cout << a->toString() << std::endl;
    return 0;
}
