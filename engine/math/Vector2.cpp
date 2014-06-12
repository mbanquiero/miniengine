#include "stdafx.h"
#include "Vector2.h"

Vector2::Vector2()
{

}

Vector2::Vector2( const float * vector)
{
	v[0] = vector[0];
	v[1] = vector[1];
}

Vector2::Vector2( float x, float y )
{
	v[0] = x;
	v[1] = y;
}

Vector2::~Vector2()
{

}

Vector2& Vector2::Set(float x, float y)
{
	this->X = x; this->Y = y;
	return (*this);
}


Vector2::operator float*()
{
	return (float *)v;
}

Vector2::operator const float*() const
{
	return (const float *)v;
}

Vector2& Vector2::operator+=( const Vector2& v2)
{
	X += v2.X;
	Y += v2.Y;
	return (*this);
}

Vector2& Vector2::operator-=( const Vector2& v2)
{
	X -= v2.X;
	Y -= v2.Y;
	return (*this);
}

Vector2& Vector2::operator*=( float val )
{
	X *= val;
	Y *= val;
	return (*this);
}

Vector2& Vector2::operator/=( float val )
{
	X *= val;
	Y *= val;
	return (*this);
}

Vector2 Vector2::operator+() const
{
	return Vector2(X,Y);
}

Vector2 Vector2::operator+( const Vector2& v2) const
{
	return Vector2(X+v2.X,Y+v2.Y);
}

Vector2 Vector2::operator-() const
{
	return Vector2(-X,-Y);
}

Vector2 Vector2::operator-( const Vector2& v2) const
{
	return Vector2(X+v2.X,Y+v2.Y);
}

Vector2 Vector2::operator*( float val) const
{
	return Vector2(X*val,Y*val);
}

Vector2 Vector2::operator/( float val) const
{
	return Vector2(X/val,Y/val);
}

bool Vector2::operator==( const Vector2& v2) const
{
	return X==v2.X && Y==v2.Y;;
}

bool Vector2::operator!=( const Vector2& v2) const
{
	return !((*this)== v2);
}


float Vector2::LengthSq() const
{
	return X*X + Y*Y;
}

float Vector2::Length() const
{
	return (float)sqrt(LengthSq());
}

float Vector2::Normalize()
{
	float len = Length();
	(*this) /= len;
	return len;
}

// retorna un vector normal a si mismo 
Vector2 Vector2::normal()
{
	return(Vector2(-Y,X));
}
