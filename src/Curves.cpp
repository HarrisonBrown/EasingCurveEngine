#include "Curves.h"


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

int LinearCurve::Query(float t)
{
	auto a = ((x_tmax - x_t0) / duration);
	return (a * t) + x_t0;
}