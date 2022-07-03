#pragma once

#include "EasingCurve.h"

class LinearCurve :
    public EasingCurve
{
public:
    LinearCurve(int _x_t0, int _x_tmax, float _duration) { x_t0 = _x_t0; x_tmax = _x_tmax; duration = _duration; }
    int Query(float t) override;
};

