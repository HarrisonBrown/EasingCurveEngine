#include "Curves.h"


EasingCurve* EasingCurve::Create(CurveParameters parameters)
{
	switch (parameters.type)
	{
	case CurveType::LINEAR:
		return new LinearCurve(parameters.x_t0, parameters.x_tmax, parameters.duration);
		break;
	case CurveType::INQUAD:
		return new InQuadCurve(parameters.x_t0, parameters.x_tmax, parameters.duration);
		break;
	case CurveType::OUTQUAD:
		return new OutQuadCurve(parameters.x_t0, parameters.x_tmax, parameters.duration);
		break;
	case CurveType::INOUTQUAD:
		return new InOutQuadCurve(parameters.x_t0, parameters.x_tmax, parameters.duration);
		break;
	default:
		break;
	}
	return nullptr;
}

int LinearCurve::Query(float t)
{
	return roundf((((x_tmax - x_t0) / duration) * t) + x_t0);
}

int InQuadCurve::Query(float t)
{
	return roundf(((x_tmax - x_t0) / (duration * duration)) * (t*t) + x_t0);
}

int OutQuadCurve::Query(float t)
{
	return roundf(((x_t0 - x_tmax) / ((duration * duration) * -1)) * (((t - duration) * (t - duration)) * -1) + x_tmax);
}

int InOutQuadCurve::Query(float t)
{

	return (((x_tmax - x_t0) / duration) * t) + x_t0;
}