/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "stdafx.h"

/**
* Math utils
*/
class FastMath
{
public:
	static const float PI;
	static const float HALF_PI;
	static const float TWO_PI;
	static const float QUARTER_PI;
	static const float INV_PI;
	static const float INV_TWO_PI;
	static const float E;
	static const float RADIANS_TO_DEGREES;
	static const float DEGREES_TO_RADIANS;
};

const float FastMath::PI = 3.14159265358979323846f;
const float FastMath::HALF_PI = FastMath::PI / 2;
const float FastMath::TWO_PI = FastMath::PI * 2;
const float FastMath::QUARTER_PI = FastMath::PI / 4;
const float FastMath::INV_PI = 1 / FastMath::PI;
const float FastMath::INV_TWO_PI = 1 / FastMath::TWO_PI;
const float FastMath::E = 2.71828182845904523536f;
const float FastMath::RADIANS_TO_DEGREES = 180.0f / PI;
const float FastMath::DEGREES_TO_RADIANS = PI / 180.0f;


//Agrego intrinsics de manera global
float clamp(float x, float min, float max)
{	
	return x <= min ? min : (x >= max ? max : x);
}

float frac(float x)
{
	x = fabs(x);
	return x - floorf(x);
}

float lerp(float x, float y, float s)
{
	return x + s*(y - x);
}

float saturate(float x)
{
	return clamp(x, 0.0f, 1.0f);
}
