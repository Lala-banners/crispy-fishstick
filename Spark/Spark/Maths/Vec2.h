#pragma once

#include <raylib/raylib.h>

#include <string>
#include <initializer_list>

using std::string;
using std::initializer_list;

#define VEC_2_SIZE 2

class Vec2
{
public:
	union
	{
		struct
		{
			float x;
			float y;
		};

		float data[VEC_2_SIZE];
	};

public:
	static Vec2 one;
	static Vec2 zero;
	static Vec2 half;
	static Vec2 up;
	static Vec2 down;
	static Vec2 left;
	static Vec2 right;

public:
	Vec2();
	Vec2(float _scalar);
	Vec2(float _x, float _y);
	Vec2(initializer_list<float> _values);
	Vec2(Vector2 _pos);

	Vec2(const Vec2& _other);
	Vec2(Vec2&& _other) noexcept;

	~Vec2();

public:
	static Vec2 Add(const Vec2& _lhs, const Vec2& _rhs);
	static Vec2 Subtract(const Vec2& _lhs, const Vec2& _rhs);
	static Vec2 Scale(const Vec2& _lhs, float _rhs);

	static Vec2 Normalised(const Vec2& _vec);
	static float Distance(const Vec2& _a, const Vec2& _b);

	static float Dot(const Vec2& _lhs, const Vec2& _rhs);

	static Vec2 Lerp(const Vec2& _a, const Vec2& _b, float _t);

	static Vec2 CreateRotationVector(float _radians);

public:
	float Dot(const Vec2& _rhs) const;

	float Magnitude() const;
	float MagnitudeSqr() const;

	void Normalise();
	Vec2 Normalised() const;

	float Rotation() const;

	void Rotate(float _amount);
	void RotateAround(const Vec2& _pivot, float _amount);

	string ToString() const;

public:
	operator Vector2() const;

	bool operator ==(const Vec2& _other) const;
	bool operator !=(const Vec2& _other) const;

	Vec2 operator -(const Vec2& _other) const;
	Vec2& operator -=(const Vec2& _other);

	Vec2 operator +(const Vec2& _other) const;
	Vec2& operator +=(const Vec2& _other);

	Vec2 operator *(float _other) const;
	Vec2& operator *=(float _other);

	Vec2 operator *(const Vec2& _other) const;
	Vec2& operator *=(const Vec2& _other);

	Vec2& operator=(const Vec2& _other);
	Vec2& operator=(Vec2&& _other) noexcept;

	Vec2& operator=(Vector2 _other);
};

extern Vec2 operator*(float _lhs, const Vec2& _rhs);