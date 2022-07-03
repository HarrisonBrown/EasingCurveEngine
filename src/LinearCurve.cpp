#include "LinearCurve.h"

int LinearCurve::Query(float t)
{
	auto a = ((x_tmax - x_t0) / duration);
	return ( a * t) + x_t0;
}