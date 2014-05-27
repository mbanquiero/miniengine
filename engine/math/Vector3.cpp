#include "stdafx.h"
#include "Vector3.h"

Vector3::Vector3()
{
	ZeroMemory(v,sizeof(v));
}

Vector3::Vector3( const float * v2)
{
	memcpy(v,v2,sizeof(v));
}

Vector3::Vector3( float x, float y, float z )
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

Vector3::Vector3(const D3DXVECTOR3 &v)
{
	*this = *((Vector3*)&v);
}

Vector3::~Vector3()
{

}

Vector3& Vector3::Set(float x, float y, float z)
{
	this->X = x; this->Y = y; this->Z = z;
	return (*this);
}

Vector3::operator float*()
{
	return (float*)v;
}

Vector3::operator const float*() const
{
	return (const float*)v;
}

Vector3& Vector3::operator+=( const Vector3& v2)
{
	v[0] += v2.X;
	v[1] += v2.Y;
	v[2] += v2.Z;

	return (*this);
}

Vector3& Vector3::operator-=( const Vector3& v2)
{
	v[0] -= v2.X;
	v[1] -= v2.Y;
	v[2] -= v2.Z;
	
	return (*this);
}

Vector3& Vector3::operator*=( float val)
{
	v[0] *= val;
	v[1] *= val;
	v[2] *= val;
	
	return (*this);
}

Vector3& Vector3::operator/=( float val)
{
	v[0] /= val;
	v[1] /= val;
	v[2] /= val;
	
	return (*this);
}

Vector3 Vector3::operator+(const Vector3& v2) const
{
	return Vector3(v[0] + v2.X, v[1] + v2.Y, v[2] + v2.Z);
}

Vector3 Vector3::operator-( const Vector3& v2) const
{
	return Vector3(v[0] - v2.X, v[1] - v2.Y, v[2] - v2.Z);
}

Vector3 Vector3::operator*( float val) const
{
	return Vector3(X*val, Y*val, Z*val);
}

Vector3 Vector3::operator/( float val) const
{
	return Vector3(X/val, Y/val, Z/val);
}

bool Vector3::operator==( const Vector3& v2) const
{
	return X==v2.X && Y==v2.Y && Z==v2.Z;
}

bool Vector3::operator!=( const Vector3& v2) const
{
	return !((*this) == v2);
}

float Vector3::Dot( const Vector3 &v ) const
{
	return Vector3::Dot((*this), v);
}

Vector3 Vector3::Cross( const Vector3 &v ) const
{
	return Vector3::Cross((*this), v);
}

float Vector3::LengthSq() const
{
	return X*X + Y*Y + Z*Z;
}

float Vector3::Length() const
{
	return (float)sqrt(LengthSq());
}

float Vector3::Normalize()
{
	float len = Length();
	(*this) /= len;
	return len;
}

//Static functions
float Vector3::Dot( const Vector3 &v1, const Vector3 &v2 )
{
	return v1.X*v2.X + v1.Y*v2.Y + v1.Z*v2.Z;
}

Vector3 Vector3::Cross( const Vector3 &v1, const Vector3 &v2 )
{
	return Vector3(
		v1.Y*v2.Z - v1.Z*v2.Y,
		v1.Z*v2.X - v1.X*v2.Z,
		v1.X*v2.Y - v1.Y*v2.X
		);
}


Vector3 Vector3::Normalize( const Vector3 &v )
{
	return v/v.Length();
}

Vector3::operator D3DXVECTOR3*() const
{
	return (D3DXVECTOR3*)this;
}

Vector3::operator D3DXVECTOR3() const
{
	return *((D3DXVECTOR3*)this);
}

Vector4 Vector3::Transform( const Vector3 &v, const Matrix &mat )
{
	return Vector4::Transform(Vector4(v.X,v.Y,v.Z, 1), mat);
}

Vector4 Vector3::TransformCoordinate( const Vector3 &v, const Matrix &mat)
{
	return Vector4::Transform(Vector4(v.X,v.Y,v.Z, 1), mat);
}

Vector4 Vector3::TransformNormal( const Vector3 &v, const Matrix &mat )
{
	return Vector4::Transform(Vector4(v.X,v.Y,v.Z, 0), mat);
}




