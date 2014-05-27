#include "stdafx.h"

#include "Vector4.h"
#include "Vector3.h"


Vector4::Vector4()
{
	ZeroMemory(v, sizeof(v));
}

Vector4::Vector4( float x, float y, float z, float w )
{
	X = x;
	Y = y;
	Z = z;
	W = w;
}

Vector4::~Vector4()
{

}

Vector4::operator float*()
{
	return (float *)v;
}

Vector4& Vector4::Set(float x, float y, float z, float w)
{
	this->X = x; this->Y = y; this->Z = z; this->W = w;
	return (*this);
}

Vector4::operator const float*() const
{
	return (const float *)v;
}

Vector4& Vector4::operator+=( const Vector4& v2)
{
	X += v2.X;
	Y += v2.Y;
	Z += v2.Z;
	W += v2.W;
	return (*this);
}

Vector4& Vector4::operator-=( const Vector4& v2)
{
	X -= v2.X;
	Y -= v2.Y;
	Z -= v2.Z;
	W -= v2.W;
	return (*this);
}

Vector4& Vector4::operator*=( float val )
{
	X *= val;
	Y *= val;
	Z *= val;
	W *= val;
	return (*this);
}

Vector4& Vector4::operator/=( float val )
{
	X *= val;
	Y *= val;
	Z *= val;
	W *= val;
	return (*this);
}

Vector4 Vector4::operator+() const
{
	return Vector4(X,Y,Z,W);
}

Vector4 Vector4::operator+( const Vector4& v2) const
{
	return Vector4(X+v2.X,Y+v2.Y,Z+v2.Z,W+v2.W);
}

Vector4 Vector4::operator-() const
{
	return Vector4(-X,-Y,-Z,-W);
}

Vector4 Vector4::operator-( const Vector4& v2) const
{
	return Vector4(X+v2.X,Y+v2.Y,Z+v2.Z,W+v2.W);
}

Vector4 Vector4::operator*( float val) const
{
	return Vector4(X*val,Y*val,Z*val,W*val);
}

Vector4 Vector4::operator/( float val) const
{
	return Vector4(X/val,Y/val,Z/val,W/val);
}

bool Vector4::operator==( const Vector4& v2) const
{
	return X==v2.X && Y==v2.Y && Z==v2.Z && W==v2.W;
}

bool Vector4::operator!=( const Vector4& v2) const
{
	return !((*this)== v2);
}

Vector4 Vector4::Transform( const Vector4& v2, const Matrix & mat )
{
	return Vector4(
		v2.X*mat.M11 + v2.Y*mat.M21 + v2.Z*mat.M31 + v2.W*mat.M41,
		v2.X*mat.M12 + v2.Y*mat.M22 + v2.Z*mat.M32 + v2.W*mat.M42,
		v2.X*mat.M13 + v2.Y*mat.M23 + v2.Z*mat.M33 + v2.W*mat.M43,
		v2.X*mat.M14 + v2.Y*mat.M24 + v2.Z*mat.M34 + v2.W*mat.M44
		);
}

Vector3 Vector4::XYZ()
{ 
	return Vector3(X, Y, Z);
}


