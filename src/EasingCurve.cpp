#include "Easingcurve.h"
#include "LinearCurve.h"


EasingCurve* EasingCurve::Create(CurveParameters parameters)
{
	switch (parameters.type)
	{
	case CurveType::LINEAR:
		return new LinearCurve(parameters.x_t0, parameters.x_tmax, parameters.duration);
		break;
	default:
		break;
	}
	return nullptr;
}