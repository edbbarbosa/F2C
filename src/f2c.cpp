#include "f2c.h"
#include <iostream>

f2c::f2c(float f) {
    this->c = (f-32) * 5/9;
}

float f2c::getC(){
    return this->c;
}
