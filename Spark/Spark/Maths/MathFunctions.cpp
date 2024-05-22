#include "MathFunctions.h"

#include <cfloat>

bool Compare(const float _x, const float _y)
{
	return fabsf(_x - _y) <= (FLT_EPSILON + 0.000001f) * fmaxf(1.f, fmaxf(fabsf(_x), fabsf(_y)));
}

float Clamp01(const float _val)
{
	if (_val < 0.f)
		return 0.f;

	if (_val > 1.f)
		return 1.f;

	return _val;
}