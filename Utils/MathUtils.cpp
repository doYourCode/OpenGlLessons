#include "Math.h"

#include <cassert>

namespace Utils
{
	namespace Math
	{
		float ClampSwap(float x, float min, float max)
		{
			assert(max > min);

			float r = x < min ? max : x;
			return x > max ? min : r;
		}
	}
}