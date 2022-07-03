#pragma once

#include <vector>
#include <string>

using Parameter = std::pair<std::string, std::string>;

enum CurveType
{
	UNSET = -1,
	LINEAR = 0,
	INQUAD,
	OUTQUAD,
	INOUTQUAD,
};

struct CurveParameters
{
	CurveType type;
	int x_t0;
	int x_tmax;
	float duration;
};

class EasingCurve
{
protected:
	int x_t0;
	int x_tmax;
	float duration;

public:
	static EasingCurve* Create(CurveParameters _parameters);
	virtual int Query(float t) = 0;
};

