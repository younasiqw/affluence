#pragma once

class math
{
public:
	float clip(float n, float lower, float upper)
	{
		n = (n > lower) * n + !(n > lower) * lower;
		return (n < upper) * n + !(n < upper) * upper;
	}

	template<class T, class U>
	T clamp(T in, U low, U high)
	{
		if (in <= low)
			return low;

		if (in >= high)
			return high;

		return in;
	}
};

extern math g_math;