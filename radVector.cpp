#include "radVector.h"
#include <math.h>

radVector::radVector(float x, float y):
_x(x),
_y(y),
_lenght(sqrt(x*x + y*y)) {}

float radVector::lenght() const {
    return _lenght;
}

radVector radVector::operator -(const radVector& vec) const {
    return radVector(_x-vec._x, _y-vec._y);
}

radVector radVector::operator +(const radVector& vec) const {
    return radVector(_x+vec._x, _y+vec._y);
}

float radVector::operator *(const radVector& vec) const {
    return (_x*vec._x + _y*vec._y);
}

radVector radVector::operator /(float operand) const {
    return radVector(_x / operand, _y / operand);
}

std::ostream& operator<<(std::ostream& os, const radVector& operand) {
    os << "(" << operand._x << "," << operand._y << ")";
    return os;
}

bool radVector::operator ==(const radVector& vec) const {
    return _x == vec._x && _y == vec._y;
}

radVector& radVector::operator =(const radVector& vec) {
    if (*this == vec) {
        return *this;
    }
    _x = vec._x;
    _y = vec._y;
    _lenght = sqrt(_x*_x + _y*_y);
    return *this;
}
