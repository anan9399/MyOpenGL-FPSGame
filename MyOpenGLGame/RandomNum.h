#pragma once
#include <iostream>
#include <random>
class RandomNum
{
public:
	static RandomNum& GetInstance()
	{
		static RandomNum instance;
		return instance;
	};

	float GetRandomNumber1f(float min, float max);

private:
	std::mt19937 rng;
};

