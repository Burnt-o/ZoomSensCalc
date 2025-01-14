#pragma once
#include "WinUtilities.h"
#include "Constants.h"
#include <cassert>

class ViewAngle
{
public:
	float data;
	operator float() const { return data; }
	ViewAngle(float d) : data(d) { assert(d >= 0.f && d <= twoPiRadians); }
};

static inline std::wstring ToString(const ViewAngle& t) { return StringToWString(ExactFloatToString(t.data)); }