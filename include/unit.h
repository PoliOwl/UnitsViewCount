#pragma once

#include "radVector.h"
#include <math.h>

class unit {
  public:
    unit(float sector, float viewDistance, const radVector &viewDirection, const radVector &position):
        _angle(cos(sector / 2)),
        _viewDistance(viewDistance),
        _viewDirection(viewDirection),
        _position(position) {};

    bool isInView(radVector point) const;
    radVector getPosition() const { return _position; }
    radVector getViewDirection() const { return _viewDirection; }

  private:
    float _angle;
    float _viewDistance;
    radVector _viewDirection;
    radVector _position;
};
