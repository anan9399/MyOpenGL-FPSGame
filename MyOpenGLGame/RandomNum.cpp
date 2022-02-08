#include "RandomNum.h"


float RandomNum::GetRandomNumber1f(float min, float max)
{
	std::uniform_real_distribution<float> result(min, max);
	return result(rng);
}


