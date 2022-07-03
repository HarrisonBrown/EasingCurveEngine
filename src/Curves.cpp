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
	// Split duration in two, treating values for the first half as InQuadCurves and values for the second half as OutQuadCurves

	int x_thalf = x_t0 + ((x_tmax - x_t0) / 2);
	if (t <= duration / 2)
	{
		// From t0 to thalf for duration/2
		CurveParameters firstHalfParams{ CurveType::INQUAD, x_t0, x_thalf, duration / 2 };
		return EasingCurve::Create(firstHalfParams)->Query(t / 2);
	}
	else
	{
		// From thalf to tmax for duration/2
		CurveParameters secondHalfParams{ CurveType::OUTQUAD, x_thalf, x_tmax, duration / 2 };

		// As equation vertex will be on duration/2, shift t back by the same amount
		return EasingCurve::Create(secondHalfParams)->Query(t - (duration / 2));
	}
}
