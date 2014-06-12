
#pragma once


struct Vector2  
{
public:
	union
	{
		struct
		{
			float X,Y;
		};
		float v[2];
	};
public:
	Vector2();
	Vector2( const float * vector);
	Vector2( float x, float y);
	~Vector2();

	Vector2& Set(float x, float y);

	// casting
    operator float* ();
    operator const float* () const;
	
    // assignment operators
    Vector2& operator += ( const Vector2& v2);
    Vector2& operator -= ( const Vector2& v2);
    Vector2& operator *= ( float val);
    Vector2& operator /= ( float val);
	
    // unary operators
    Vector2 operator + () const;
    Vector2 operator - () const;
	
    // binary operators
    Vector2 operator + ( const Vector2& v2) const;
    Vector2 operator - ( const Vector2& v2) const;
    Vector2 operator * ( float val) const;
    Vector2 operator / ( float val) const;
	
    friend Vector2 operator * ( float, const Vector2& );
	
    bool operator == ( const Vector2& v2) const;
    bool operator != ( const Vector2& v2) const;


	float LengthSq() const;
	float Length() const;
	float Normalize();
	Vector2 normal();
    
    

};
