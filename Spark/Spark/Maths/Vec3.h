#pragma once

#include <raylib/raylib.h>

#include <string>
#include <initializer_list>

using std::string;
using std::initializer_list;

#define VEC_3_SIZE 3

class Vec3
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};

		float data[VEC_3_SIZE];
	};

public:


public:
	Vec3();
	Vec3(float _scalar);
	Vec3(float _x, float _y, float _z);
	Vec3(initializer_list<float> _values);
	Vec3(Vector3 _vector);

	Vec3(const Vec3& _other);
	Vec3(Vec3&& _other) noexcept;

	~Vec3();

public:
	static Vec3 Add(const Vec3& _lhs, const Vec3& _rhs);
	static Vec3 Subtract(const Vec3& _lhs, const Vec3& _rhs);
	static Vec3 Scale(const Vec3& _lhs, float _rhs);

	static Vec3 Normalised(const Vec3& _vec);
	static float Distance(const Vec3& _a, const Vec3& _b);

	static float Dot(const Vec3& _lhs, const Vec3& _rhs);
	static Vec3 Cross(const Vec3& _lhs, const Vec3& _rhs);

	static Vec3 Lerp(const Vec3& _a, const Vec3& _b, float _t);

public:
	float Dot(const Vec3& _rhs) const;
	Vec3 Cross(const Vec3& _rhs) const;

	float Magnitude() const;
	float MagnitudeSqr() const;

	void Normalise();
	Vec3 Normalised() const;

	string ToString() const;

public:
	operator Vector3() const;

	bool operator ==(const Vec3& _other) const;
	bool operator !=(const Vec3& _other) const;

	Vec3 operator -(const Vec3& _other) const;
	Vec3& operator -=(const Vec3& _other);

	Vec3 operator +(const Vec3& _other) const;
	Vec3& operator +=(const Vec3& _other);

	Vec3 operator *(float _other) const;
	Vec3& operator *=(float _other);

	Vec3& operator=(const Vec3& _other);
	Vec3& operator=(Vec3&& _other) noexcept;

};

extern Vec3 operator*(float _lhs, const Vec3& _rhs);