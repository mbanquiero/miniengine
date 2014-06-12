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




// producto vectorial
Vector3 Vector3::operator*(const Vector3 &q)
{
	float a=Y*q.Z-Z*q.Y;
	float b=Z*q.X-X*q.Z;
	float c=X*q.Y-Y*q.X;
	return Vector3(a,b,c);
}


// rotacion x-y es sobre el eje z
void Vector3::rotar_xy(double an)
{
	float xr = X*cos(an)-Y*sin(an);
	float yr = Y*cos(an)+X*sin(an); 
	X = xr;
	Y = yr;
}


// rotacion xz es sobre el eje y
void Vector3::rotar_xz(double an)
{

	float xr=X*cos(an)+Z*sin(an); 
	float zr=-X*sin(an)+Z*cos(an);
	X = xr;
	Z = zr;

}

// rotacion zy es sobre el eje x
void Vector3::rotar_zy(double an)
{
	float yr=Y*cos(an)-Z*sin(an);
	float zr=Z*cos(an)+Y*sin(an); 
	Y = yr;
	Z = zr;
}


// Rotacion sobre un eje arbitrario
void Vector3::rotar(Vector3 o,Vector3 eje,double theta)
{
	double a = o.X;
	double b = o.Y;
	double c = o.Z;
	double u = eje.X;
	double v = eje.Y;
	double w = eje.Z;

	double u2 = u*u;
	double v2 = v*v;
	double w2 = w*w;
	double cosT = cos(theta);
	double sinT = sin(theta);
	double l2 = u2 + v2 + w2;
	double l =  sqrt(l2);

	if(l2 < 0.000000001)		// el vector de rotacion es casi nulo
		return;

	double xr = a*(v2 + w2) + u*(-b*v - c*w + u*X + v*Y + w*Z) 
		+ (-a*(v2 + w2) + u*(b*v + c*w - v*Y - w*Z) + (v2 + w2)*X)*cosT
		+ l*(-c*v + b*w - w*Y + v*Z)*sinT;
	xr/=l2;

	double yr = b*(u2 + w2) + v*(-a*u - c*w + u*X + v*Y + w*Z) 
		+ (-b*(u2 + w2) + v*(a*u + c*w - u*X - w*Z) + (u2 + w2)*Y)*cosT
		+ l*(c*u - a*w + w*X - u*Z)*sinT;
	yr/=l2;

	double zr = c*(u2 + v2) + w*(-a*u - b*v + u*X + v*Y + w*Z) 
		+ (-c*(u2 + v2) + w*(a*u + b*v - u*X - v*Y) + (u2 + v2)*Z)*cosT
		+ l*(-b*u + a*v - v*X + u*Y)*sinT;
	zr/=l2;

	X = xr;
	Y = yr;
	Z = zr;
}

void Vector3::rotar(Vector3 o,double an_Z,double an_X,double an_Y)
{
	Vector3 eje_x = Vector3(1,0,0);
	Vector3 eje_y = Vector3(0,1,0);
	Vector3 eje_z = Vector3(0,0,1);
	Vector3 O = Vector3(0,0,0);
	// primero roto en el eje Z (plano_xy)
	rotar(o,eje_z,an_Z);
	// y roto los ejes x,y tambien, la primer rotacion se puede hacer
	// directamente, pues los ejes todavia no estan rotados
	eje_x.rotar_xy(an_Z);
	eje_y.rotar_xy(an_Z);
	// sin embargo las siguientes tienen que ser sobre los ejes ya rotados
	// Ahoro roto sobre el eje X (plano zy)
	rotar(o,eje_x,an_X);		// el pto pp dicho
	// y los ejes 
	eje_y.rotar(O,eje_x,an_X);
	// Y ahora roto sobre el eje Y (plano xz)
	rotar(o,eje_y,an_Y);		// el pto pp dicho

}



void Vector3::rotar_inv(Vector3 o,double an_Z,double an_X,double an_Y)
{
	Vector3 eje_x = Vector3(1,0,0);
	Vector3 eje_y = Vector3(0,1,0);
	Vector3 eje_z = Vector3(0,0,1);
	Vector3 O = Vector3(0,0,0);

	// Revierto la rotacion en Y 
	rotar(o,eje_y,-an_Y);		// el pto pp dicho
	// y roto los ejes x,y tambien
	eje_x.rotar_xz(-an_Y);
	eje_z.rotar_xz(-an_Y);
	// Revierto la rot. sobre el eje X (plano zy)
	rotar(o,eje_x,-an_X);		// el pto pp dicho
	eje_z.rotar(O,eje_x,-an_X);
	// y revierto la rot en el eje Z (plano_xy)
	rotar(o,eje_z,-an_Z);

}
