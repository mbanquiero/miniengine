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

//Agrego intrinsics de manera global
inline float clamp(float x, float min, float max)
{	
	return x <= min ? min : (x >= max ? max : x);
}

inline float frac(float x)
{
	x = fabs(x);
	return x - floorf(x);
}

inline float lerp(float x, float y, float s)
{
	return x + s*(y - x);
}

inline float saturate(float x)
{
	return clamp(x, 0.0f, 1.0f);
}


// retorna 1 si es positivo -1 si es negativo
inline char sign(float n)
{
	return(n<0?-1:1);
}
