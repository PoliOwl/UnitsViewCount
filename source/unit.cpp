#include "unit.h"

bool unit::isInView(radVector point) const {
    radVector vecBetween = point - _position;
    float div = _viewDirection.lenght() * vecBetween.lenght();
    float angleBetween = (_viewDirection * vecBetween) / div;
    return _angle < angleBetween && vecBetween.lenght() <= _viewDistance;
}
