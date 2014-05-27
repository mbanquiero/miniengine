
#pragma once


#include "stdafx.h"

#define MATRIX_INVERSE_EPSILON		1e-14

struct Vector3;

struct Matrix  
{

	union {
        struct {
            float        M11, M12, M13, M14;
            float        M21, M22, M23, M24;
            float        M31, M32, M33, M34;
            float        M41, M42, M43, M44;
        };
        float m[4][4];
    };


public:
	Matrix();
	Matrix(	float _m00, float _m01, float _m02, float _m03,
				float _m10, float _m11, float _m12, float _m13,
				float _m20, float _m21, float _m22, float _m23,
				float _m30, float _m31, float _m32, float _m33
			);
	~Matrix();

	operator D3DMATRIX(void) const;
	operator D3DMATRIX*(void) const;
	operator D3DXMATRIX(void) const;
	operator D3DXMATRIX*(void) const;
	void Identity();
	void Translation(float x, float y, float z);
	void RotationX(float angle);
	void RotationY(float angle);
	void RotationZ(float angle);
	void RotationYawPitchRoll(float yaw, float pitch, float roll);
	void RotationAxis(const Vector3&, float angle);
	void Scale(float sx, float sy, float sz);

	inline void LookAtLH(const Vector3 &cameraPosition, const Vector3 &cameraTarget, const Vector3 &cameraUpVector);
	void PerspectiveFovLH(float fieldOfViewY,float aspectRatio, float znearPlane, float zfarPlane);
	void Transpose();
	bool Inverse();

	// access grants
    float& operator () ( int Row, int Col );
    float  operator () ( int Row, int Col ) const;
	
    // casting operators
    operator float* ();
    operator const float* () const;
	
    // assignment operators
    Matrix& operator *= ( const Matrix& );
    Matrix& operator += ( const Matrix& );
    Matrix& operator -= ( const Matrix& );
    Matrix& operator *= ( float );
    Matrix& operator /= ( float );
	
    // unary operators
    Matrix operator + () const;
    Matrix operator - () const;
	
    // binary operators
    Matrix operator * ( const Matrix& ) const;
    Matrix operator + ( const Matrix& ) const;
    Matrix operator - ( const Matrix& ) const;
    Matrix operator * ( float ) const;
    Matrix operator / ( float ) const;
	
    friend Matrix operator * ( float, const Matrix& );
	
    bool operator == ( const Matrix& ) const;
    bool operator != ( const Matrix& ) const;

	static Matrix SIdentity();
	static Matrix STranslation(float x, float y, float z);
	static Matrix SRotationX(float angle);
	static Matrix SRotationY(float angle);
	static Matrix SRotationZ(float angle);
	static Matrix SRotationYawPitchRoll(float yaw, float pitch, float roll);
	static Matrix SRotationAxis(const Vector3 &vector, float angle);
	static Matrix SScale(float sx, float sy, float sz);
	
	static Matrix SLookAtLH(const Vector3 &cameraPosition, const Vector3 &cameraTarget, const Vector3 &cameraUpVector);
	static Matrix SPerspectiveFovLH(float fieldOfViewY,float aspectRatio, float znearPlane, float zfarPlane);
	static Matrix STranspose(const Matrix &mat);


};


