#pragma once

#include <ostream>

class radVector {
public:
    radVector(float x, float y);
    float lenght() const;
    radVector operator -(const radVector& vec) const;
    radVector operator +(const radVector& vec) const;
    float operator *(const radVector& vec) const;
    radVector operator /(float operand) const;
    bool operator ==(const radVector& vec) const;
    radVector& operator =(const radVector& vec);
    friend std::ostream& operator<<(std::ostream& os, const radVector& operand);
private:
    float _lenght;
    float _x;
    float _y;
};
