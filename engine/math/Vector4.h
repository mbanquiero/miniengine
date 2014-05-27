#pragma once

#include "Matrix.h"


struct Vector3;


struct Vector4  
{
	union
	{
		struct
		{
			float X,Y,Z,W;
		};
		float v[4];
	};
public:
	~Vector4();
	Vector4();
    Vector4( float x, float y, float z, float w );

	Vector4& Set(float x, float y, float z, float w);
	
    // casting
    operator float* ();
    operator const float* () const;
	
    // assignment operators
    Vector4& operator += ( const Vector4& v2);
    Vector4& operator -= ( const Vector4& v2);
    Vector4& operator *= ( float val);
    Vector4& operator /= ( float val);
	
    // unary operators
    Vector4 operator + () const;
    Vector4 operator - () const;
	
    // binary operators
    Vector4 operator + ( const Vector4& v2) const;
    Vector4 operator - ( const Vector4& v2) const;
    Vector4 operator * ( float val) const;
    Vector4 operator / ( float val) const;
	
    friend Vector4 operator * ( float, const Vector4& );
	
    bool operator == ( const Vector4& v2) const;
    bool operator != ( const Vector4& v2) const;

	//statics
	static Vector4 Transform( const Vector4& v2, const Matrix &mat);

	Vector3 XYZ();

};

