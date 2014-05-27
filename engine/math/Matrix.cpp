#include "stdafx.h"
#include "Matrix.h"
#include "Vector3.h"

#define DOT4HV(m1,m2,r,c) (m1[r][0]*m2[0][c]+m1[r][1]*m2[1][c]+m1[r][2]*m2[2][c]+m1[r][3]*m2[3][c])

Matrix::Matrix()
{

}

Matrix::Matrix( float _m00, float _m01, float _m02, float _m03, float _m10, float _m11, float _m12, float _m13, float _m20, float _m21, float _m22, float _m23, float _m30, float _m31, float _m32, float _m33 )
{
	m[0][0] = _m00; m[0][1] = _m01; m[0][2] = _m02; m[0][3] = _m03;
	m[1][0] = _m10; m[1][1] = _m11; m[1][2] = _m12; m[1][3] = _m13;
	m[2][0] = _m20; m[2][1] = _m21; m[2][2] = _m22; m[2][3] = _m23;
	m[3][0] = _m30; m[3][1] = _m31; m[3][2] = _m32; m[3][3] = _m33;
}

Matrix::~Matrix()
{

}

Matrix::operator D3DMATRIX( void ) const
{
	return *((D3DMATRIX*)m);
}

Matrix::operator D3DMATRIX*( void ) const
{
	return (D3DMATRIX*)m;
}

Matrix::operator D3DXMATRIX( void ) const
{
	return *((D3DXMATRIX*)m);
}

Matrix::operator D3DXMATRIX*( void ) const
{
	return (D3DXMATRIX*)m;
}

void Matrix::Identity()
{
	m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
	m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
	m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
	m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
}

void Matrix::Translation( float x, float y, float z )
{
	m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
	m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
	m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
	m[3][0] = x; m[3][1] = y; m[3][2] = z; m[3][3] = 1;	
}

void Matrix::RotationX( float angle )
{
	float sinv = (float)sin(angle);
	float cosv = (float)cos(angle);

	m[0][0] = 1;	m[0][1] = 0;		m[0][2] = sinv;		m[0][3] = 0;
	m[1][0] = 0;	m[1][1] = cosv;		m[1][2] = 0;		m[1][3] = 0;
	m[2][0] = 0;	m[2][1] = -sinv;	m[2][2] = cosv;		m[2][3] = 0;
	m[3][0] = 0;	m[3][1] = 0;		m[3][2] = 0;		m[3][3] = 1;

}

void Matrix::RotationY( float angle )
{
	float sinv = (float)sin(angle);
	float cosv = (float)cos(angle);
	
	m[0][0] = cosv;	m[0][1] = 0;		m[0][2] = -sinv;	m[0][3] = 0;
	m[1][0] = 0;	m[1][1] = 1;		m[1][2] = 0;		m[1][3] = 0;
	m[2][0] = sinv;	m[2][1] = 0;		m[2][2] = cosv;		m[2][3] = 0;
	m[3][0] = 0;	m[3][1] = 0;		m[3][2] = 0;		m[3][3] = 1;
}

void Matrix::RotationZ( float angle )
{
	float sinv = (float)sin(angle);
	float cosv = (float)cos(angle);

	m[0][0] = cosv;		m[0][1] = sinv;		m[0][2] = 0;		m[0][3] = 0;
	m[1][0] = -sinv;	m[1][1] = cosv;		m[1][2] = 0;		m[1][3] = 0;
	m[2][0] = 0;		m[2][1] = 0;		m[2][2] = 1;		m[2][3] = 0;
	m[3][0] = 0;		m[3][1] = 0;		m[3][2] = 0;		m[3][3] = 1;
}

void Matrix::RotationYawPitchRoll( float yaw, float pitch, float roll )
{
	float siny = (float)sin(yaw);
	float cosy = (float)cos(yaw);
	float sinp = (float)sin(pitch);
	float cosp = (float)cos(pitch);
	float sinr = (float)sin(roll);
	float cosr = (float)cos(roll);

	m[0][0] = cosy*cosr + siny*sinp*sinr; 
	m[0][1] = siny*cosp; 
	m[0][2] = -cosy*sinr + siny*sinp*cosr;
	m[0][3] = 0;

	m[1][0] = -siny*cosp + cosy*sinp*sinr; 
	m[1][1] = cosy*cosp;
	m[1][2] = siny*sinr + cosy*sinp*cosr; 
	m[1][3] = 0;

	m[2][0] = cosp*sinr; 
	m[2][1] = -sinp; 
	m[2][2] = cosp*cosr; 
	m[2][3] = 0;

	m[3][0] = 0; 
	m[3][1] = 0; 
	m[3][2] = 0; 
	m[3][3] = 1;
	
}


void Matrix::RotationAxis(const Vector3 &vector, float angle )
{
	float sin_a = (float)sin( angle ); 
	float cos_a = (float)cos( angle ); 
	float t = 1 - cos_a;
	
	float x_y = vector.X * vector.Y; 
	float x_z = vector.X * vector.Z; 
	float y_z = vector.Y * vector.Z; 
	
	m[0][0] = 1 + t * ( vector.X * vector.X - 1 ); 
	m[0][1] = -vector.Z * sin_a + t * x_y;     
	m[0][2] =  vector.Y * sin_a + t * x_z; 
	m[0][3] = 0; 
    
	m[1][0] = vector.Z * sin_a + t * x_y; 
	m[1][1] = 1 + t * ( vector.Y * vector.Y - 1 ); 
	m[1][2] = -vector.X * sin_a + t * y_z; 
	m[1][3] = 0; 
	
	m[2][0] = -vector.Y * sin_a + t * x_z; 
	m[2][1] =  vector.X * sin_a + t * y_z; 
	m[2][2] = 1 + t * ( vector.Z * vector.Z -1 ); 
	m[2][3] = 0; 
    
	m[3][0] = 0;          
	m[3][1] = 0; 
	m[3][2] = 0; 
	m[3][3] = 1; 
}


void Matrix::Scale( float sx, float sy, float sz )
{
	m[0][0] = sx; m[0][1] = 0;  m[0][2] = 0;  m[0][3] = 0;
	m[1][0] = 0;  m[1][1] = sy; m[1][2] = 0;  m[1][3] = 0;
	m[2][0] = 0;  m[2][1] = 0;  m[2][2] = sz; m[2][3] = 0;
	m[3][0] = 0;  m[3][1] = 0;  m[3][2] = 0;  m[3][3] = 1;
}

float& Matrix::operator()( int Row, int Col )
{
	return m[Row][Col];
}

float Matrix::operator()( int Row, int Col ) const
{
	return m[Row][Col];
}

Matrix::operator float*()
{
	return (float*)m;
}

Matrix::operator const float*() const
{
	return (const float*)m;
}

Matrix& Matrix::operator*=( const Matrix& mat)
{
	*(this) = (*(this))*mat;
	return *(this);
}

Matrix& Matrix::operator*=( float val)
{
	m[0][0] *= val;  m[0][1] *= val;  m[0][2] *= val;  m[0][3] *= val;
	m[1][0] *= val;  m[1][1] *= val;  m[1][2] *= val;  m[1][3] *= val;
	m[2][0] *= val;  m[2][1] *= val;  m[2][2] *= val;  m[2][3] *= val;
	m[3][0] *= val;  m[3][1] *= val;  m[3][2] *= val;  m[3][3] *= val;

	return *(this);
}

Matrix& Matrix::operator+=( const Matrix& m2)
{
	m[0][0] += m2.M11; m[0][1] += m2.M12; m[0][2] += m2.M13; m[0][3] += m2.M14;
	m[1][0] += m2.M21; m[1][1] += m2.M22; m[1][2] += m2.M23; m[1][3] += m2.M24;
	m[2][0] += m2.M31; m[2][1] += m2.M32; m[2][2] += m2.M33; m[2][3] += m2.M34;
	m[3][0] += m2.M41; m[3][1] += m2.M42; m[3][2] += m2.M43; m[3][3] += m2.M44;
	
	return *(this);
}

Matrix& Matrix::operator-=( const Matrix& m2)
{
	m[0][0] -= m2.M11; m[0][1] -= m2.M12; m[0][2] -= m2.M13; m[0][3] -= m2.M14;
	m[1][0] -= m2.M21; m[1][1] -= m2.M22; m[1][2] -= m2.M23; m[1][3] -= m2.M24;
	m[2][0] -= m2.M31; m[2][1] -= m2.M32; m[2][2] -= m2.M33; m[2][3] -= m2.M34;
	m[3][0] -= m2.M41; m[3][1] -= m2.M42; m[3][2] -= m2.M43; m[3][3] -= m2.M44;
	
	return *(this);
}

Matrix& Matrix::operator/=( float val)
{
	m[0][0] /= val;  m[0][1] /= val;  m[0][2] /= val;  m[0][3] /= val;
	m[1][0] /= val;  m[1][1] /= val;  m[1][2] /= val;  m[1][3] /= val;
	m[2][0] /= val;  m[2][1] /= val;  m[2][2] /= val;  m[2][3] /= val;
	m[3][0] /= val;  m[3][1] /= val;  m[3][2] /= val;  m[3][3] /= val;
	
	return *(this);
}

Matrix Matrix::operator+() const
{
	return (*this);
}

Matrix Matrix::operator+( const Matrix& m2) const
{
	return Matrix(
		m[0][0]+m2.m[0][0],m[0][1]+m2.m[0][1],m[0][2]+m2.m[0][2],m[0][3]+m2.m[0][3],
		m[1][0]+m2.m[1][0],m[1][1]+m2.m[1][1],m[1][2]+m2.m[1][2],m[1][3]+m2.m[1][3],
		m[2][0]+m2.m[2][0],m[2][1]+m2.m[2][1],m[2][2]+m2.m[2][2],m[2][3]+m2.m[2][3],
		m[3][0]+m2.m[3][0],m[3][1]+m2.m[3][1],m[3][2]+m2.m[3][2],m[3][3]+m2.m[3][3]);
}

Matrix Matrix::operator-() const
{
	return (*this)*-1;
}

Matrix Matrix::operator*( const Matrix& m2) const
{
	return Matrix(
		DOT4HV(m,m2.m,0,0),DOT4HV(m,m2.m,0,1),DOT4HV(m,m2.m,0,2),DOT4HV(m,m2.m,0,3),
		DOT4HV(m,m2.m,1,0),DOT4HV(m,m2.m,1,1),DOT4HV(m,m2.m,1,2),DOT4HV(m,m2.m,1,3),
		DOT4HV(m,m2.m,2,0),DOT4HV(m,m2.m,2,1),DOT4HV(m,m2.m,2,2),DOT4HV(m,m2.m,2,3),
		DOT4HV(m,m2.m,3,0),DOT4HV(m,m2.m,3,1),DOT4HV(m,m2.m,3,2),DOT4HV(m,m2.m,3,3));

}

Matrix Matrix::operator*( float val) const
{
	return Matrix(
		m[0][0]*val,m[0][1]*val,m[0][2]*val,m[0][3]*val,
		m[1][0]*val,m[1][1]*val,m[1][2]*val,m[1][3]*val,
		m[2][0]*val,m[2][1]*val,m[2][2]*val,m[2][3]*val,
		m[3][0]*val,m[3][1]*val,m[3][2]*val,m[3][3]*val);
}

Matrix Matrix::operator-( const Matrix& m2) const
{
	return Matrix(
		m[0][0]-m2.m[0][0],m[0][1]-m2.m[0][1],m[0][2]-m2.m[0][2],m[0][3]-m2.m[0][3],
		m[1][0]-m2.m[1][0],m[1][1]-m2.m[1][1],m[1][2]-m2.m[1][2],m[1][3]-m2.m[1][3],
		m[2][0]-m2.m[2][0],m[2][1]-m2.m[2][1],m[2][2]-m2.m[2][2],m[2][3]-m2.m[2][3],
		m[3][0]-m2.m[3][0],m[3][1]-m2.m[3][1],m[3][2]-m2.m[3][2],m[3][3]-m2.m[3][3]);
}

Matrix Matrix::operator/( float val) const
{
	return Matrix(
		m[0][0]/val,m[0][1]/val,m[0][2]/val,m[0][3]/val,
		m[1][0]/val,m[1][1]/val,m[1][2]/val,m[1][3]/val,
		m[2][0]/val,m[2][1]/val,m[2][2]/val,m[2][3]/val,
		m[3][0]/val,m[3][1]/val,m[3][2]/val,m[3][3]/val);
}

bool Matrix::operator==( const Matrix& m2) const
{
	return
		m[0][0]==m2.m[0][0] && m[0][1]==m2.m[0][1] && m[0][2]==m2.m[0][2] && m[0][3]==m2.m[0][3] &&
		m[1][0]==m2.m[1][0] && m[1][1]==m2.m[1][1] && m[1][2]==m2.m[1][2] && m[1][3]==m2.m[1][3] &&
		m[2][0]==m2.m[2][0] && m[2][1]==m2.m[2][1] && m[2][2]==m2.m[2][2] && m[2][3]==m2.m[2][3] &&
		m[3][0]==m2.m[3][0] && m[3][1]==m2.m[3][1] && m[3][2]==m2.m[3][2] && m[3][3]==m2.m[3][3];
}

bool Matrix::operator!=( const Matrix& m2) const
{
	return !((*this)==m2);
}

void Matrix::LookAtLH( const Vector3 &cameraPosition, const Vector3 &cameraTarget, const Vector3 &cameraUpVector )
{
	Vector3 zaxis = Vector3::Normalize(cameraTarget-cameraPosition);
	Vector3 xaxis = Vector3::Normalize(cameraUpVector.Cross(zaxis));
	Vector3 yaxis = Vector3::Normalize(zaxis.Cross(xaxis));

	m[0][0] = xaxis.X; m[0][1] = yaxis.X; m[0][2] = zaxis.X; m[0][3] = 0;
	m[1][0] = xaxis.Y; m[1][1] = yaxis.Y; m[1][2] = zaxis.Y, m[1][3] = 0;
	m[2][0] = xaxis.Z; m[2][1] = yaxis.Z; m[2][2] = zaxis.Z, m[2][3] = 0;
	m[3][0] = -xaxis.Dot(cameraPosition); m[3][1] = -yaxis.Dot(cameraPosition); m[3][2] = -zaxis.Dot(cameraPosition); m[3][3] = 1;
}

void Matrix::PerspectiveFovLH( float fieldOfViewY,float aspectRatio, float znearPlane, float zfarPlane )
{
	//cotangente(x) = tan(PI/2 - x)
	float h = (float)tan(1.57079633 - fieldOfViewY/2);
	float w = h/aspectRatio;
	
	m[0][0] = w; m[0][1] = 0; m[0][2] = 0;									m[0][3] = 0;
	m[1][0] = 0; m[1][1] = h; m[1][2] = 0;									m[1][3] = 0;
	m[2][0] = 0; m[2][1] = 0; m[2][2] = zfarPlane/(zfarPlane-znearPlane);	m[2][3] = 1;
	m[3][0] = 0; m[3][1] = 0; m[3][2] = -znearPlane*zfarPlane/(zfarPlane-znearPlane);	m[3][3] = 0;
}

Matrix Matrix::STranslation( float x, float y, float z )
{
	Matrix mat;
	mat.Translation(x,y,z);
	return mat;	
}

Matrix Matrix::SIdentity()
{
	Matrix mat;
	mat.Identity();
	return mat;	
}

Matrix Matrix::SRotationX( float angle )
{
	Matrix mat;
	mat.RotationX(angle);
	return mat;	
}

Matrix Matrix::SRotationY( float angle )
{
	Matrix mat;
	mat.RotationY(angle);
	return mat;	
}

Matrix Matrix::SRotationZ( float angle )
{
	Matrix mat;
	mat.RotationZ(angle);
	return mat;	
}

Matrix Matrix::SRotationYawPitchRoll( float yaw, float pitch, float roll )
{
	Matrix mat;
	mat.RotationYawPitchRoll(yaw,pitch,roll);
	return mat;	
}

Matrix Matrix::SRotationAxis( const Vector3 &vector, float angle )
{
	Matrix mat;
	mat.RotationAxis(vector,angle);
	return mat;	
}

Matrix Matrix::SScale( float sx, float sy, float sz )
{
	Matrix mat;
	mat.Scale(sx,sy,sz);
	return mat;	
}

Matrix Matrix::SLookAtLH( const Vector3 &cameraPosition, const Vector3 &cameraTarget, const Vector3 &cameraUpVector )
{
	Matrix mat;
	mat.LookAtLH(cameraPosition, cameraTarget,cameraUpVector);
	return mat;
}

Matrix Matrix::SPerspectiveFovLH( float fieldOfViewY,float aspectRatio, float znearPlane, float zfarPlane )
{
	Matrix mat;
	mat.PerspectiveFovLH(fieldOfViewY,aspectRatio, znearPlane, zfarPlane);
	return mat;	
}

void Matrix::Transpose()
{
	float aux;

#define SWAP(a,b) aux=a;a=b;b=aux;
	
	SWAP(m[0][1],m[1][0])
	SWAP(m[0][2],m[2][0])
	SWAP(m[0][3],m[3][0])
	SWAP(m[1][2],m[2][1])
	SWAP(m[1][3],m[3][1])
	SWAP(m[2][3],m[3][2])
}

Matrix Matrix::STranspose( const Matrix &mat )
{
	Matrix rta = mat;
	rta.Transpose();
	return rta;
}

bool Matrix::Inverse()
{
	// 84+4+16 = 104 multiplications
	//			   1 division
	double det, invDet;
	
	// 2x2 sub-determinants required to calculate 4x4 determinant
	float det2_01_01 = m[0][0] * m[1][1] - m[1][0] * m[0][1];
	float det2_01_02 = m[0][0] * m[2][1] - m[2][0] * m[0][1];
	float det2_01_03 = m[0][0] * m[3][1] - m[3][0] * m[0][1];
	float det2_01_12 = m[1][0] * m[2][1] - m[2][0] * m[1][1];
	float det2_01_13 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
	float det2_01_23 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
	
	// 3x3 sub-determinants required to calculate 4x4 determinant
	float det3_201_012 = m[0][2] * det2_01_12 - m[1][2] * det2_01_02 + m[2][2] * det2_01_01;
	float det3_201_013 = m[0][2] * det2_01_13 - m[1][2] * det2_01_03 + m[3][2] * det2_01_01;
	float det3_201_023 = m[0][2] * det2_01_23 - m[2][2] * det2_01_03 + m[3][2] * det2_01_02;
	float det3_201_123 = m[1][2] * det2_01_23 - m[2][2] * det2_01_13 + m[3][2] * det2_01_12;
	
	det = ( - det3_201_123 * m[0][3] + det3_201_023 * m[1][3] - det3_201_013 * m[2][3] + det3_201_012 * m[3][3] );
	
	if ( fabs( det ) < MATRIX_INVERSE_EPSILON ) {
		return false;
	}
	
	invDet = 1.0f / det;
	
	// remaining 2x2 sub-determinants
	float det2_03_01 = m[0][0] * m[1][3] - m[1][0] * m[0][3];
	float det2_03_02 = m[0][0] * m[2][3] - m[2][0] * m[0][3];
	float det2_03_03 = m[0][0] * m[3][3] - m[3][0] * m[0][3];
	float det2_03_12 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
	float det2_03_13 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
	float det2_03_23 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
	
	float det2_13_01 = m[0][1] * m[1][3] - m[1][1] * m[0][3];
	float det2_13_02 = m[0][1] * m[2][3] - m[2][1] * m[0][3];
	float det2_13_03 = m[0][1] * m[3][3] - m[3][1] * m[0][3];
	float det2_13_12 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
	float det2_13_13 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
	float det2_13_23 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
	
	// remaining 3x3 sub-determinants
	float det3_203_012 = m[0][2] * det2_03_12 - m[1][2] * det2_03_02 + m[2][2] * det2_03_01;
	float det3_203_013 = m[0][2] * det2_03_13 - m[1][2] * det2_03_03 + m[3][2] * det2_03_01;
	float det3_203_023 = m[0][2] * det2_03_23 - m[2][2] * det2_03_03 + m[3][2] * det2_03_02;
	float det3_203_123 = m[1][2] * det2_03_23 - m[2][2] * det2_03_13 + m[3][2] * det2_03_12;
	
	float det3_213_012 = m[0][2] * det2_13_12 - m[1][2] * det2_13_02 + m[2][2] * det2_13_01;
	float det3_213_013 = m[0][2] * det2_13_13 - m[1][2] * det2_13_03 + m[3][2] * det2_13_01;
	float det3_213_023 = m[0][2] * det2_13_23 - m[2][2] * det2_13_03 + m[3][2] * det2_13_02;
	float det3_213_123 = m[1][2] * det2_13_23 - m[2][2] * det2_13_13 + m[3][2] * det2_13_12;
	
	float det3_301_012 = m[0][3] * det2_01_12 - m[1][3] * det2_01_02 + m[2][3] * det2_01_01;
	float det3_301_013 = m[0][3] * det2_01_13 - m[1][3] * det2_01_03 + m[3][3] * det2_01_01;
	float det3_301_023 = m[0][3] * det2_01_23 - m[2][3] * det2_01_03 + m[3][3] * det2_01_02;
	float det3_301_123 = m[1][3] * det2_01_23 - m[2][3] * det2_01_13 + m[3][3] * det2_01_12;
	
	m[0][0] =	- det3_213_123 * invDet;
	m[1][0] = + det3_213_023 * invDet;
	m[2][0] = - det3_213_013 * invDet;
	m[3][0] = + det3_213_012 * invDet;
	
	m[0][1] = + det3_203_123 * invDet;
	m[1][1] = - det3_203_023 * invDet;
	m[2][1] = + det3_203_013 * invDet;
	m[3][1] = - det3_203_012 * invDet;
	
	m[0][2] = + det3_301_123 * invDet;
	m[1][2] = - det3_301_023 * invDet;
	m[2][2] = + det3_301_013 * invDet;
	m[3][2] = - det3_301_012 * invDet;
	
	m[0][3] = - det3_201_123 * invDet;
	m[1][3] = + det3_201_023 * invDet;
	m[2][3] = - det3_201_013 * invDet;
	m[3][3] = + det3_201_012 * invDet;
	
	return true;
}

