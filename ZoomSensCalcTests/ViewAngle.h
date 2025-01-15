#pragma once
#include "WinUtilities.h"
#include "Constants.h"
#include <cassert>

// This class serves two purposes:
// a) constrain construction to 0 >= f >= twoPiRadians (note; subsequent math on the data member is NOT constrained)
// b) override ToString operator to use ExactFloatToString for the purpose of unit testing assert messages.
class ViewAngle
{
public:
	float data;
	operator float() const { return data; }
	ViewAngle(float f) : data(f) { assert(f >= 0.f && f <= twoPiRadians); }
};

static inline std::wstring ToString(const ViewAngle& t) { return StringToWString(ExactFloatToString(t.data)); }