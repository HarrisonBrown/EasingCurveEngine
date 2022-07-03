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


class LinearCurve :
	public EasingCurve
{
public:
	LinearCurve(int _x_t0, int _x_tmax, float _duration) { x_t0 = _x_t0; x_tmax = _x_tmax; duration = _duration; }
	int Query(float t) override;
};

