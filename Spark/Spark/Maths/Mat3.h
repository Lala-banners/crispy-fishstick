#pragma once

#include "Vec2.h"
#include "Vec3.h"

#include <string>

using std::string;

#define MAT_3_SIZE (VEC_3_SIZE * VEC_3_SIZE)

class Mat3
{
public:
	union
	{
		struct
		{
			// 11 12 13
			// 21 22 23
			// 31 32 33

			float m1; // 11
			float m2; // 21
			float m3; // 31
			float m4; // 12
			float m5; // 22
			float m6; // 32
			float m7; // 13
			float m8; // 23
			float m9; // 33
		};

		float data[MAT_3_SIZE];
	};


public:
	Mat3();
	Mat3(float _scalar);
	Mat3(float _m1, float _m4, float _m7,
		float _m2, float _m5, float _m8,
		float _m3, float _m6, float _m9);
	Mat3(float _matrix[MAT_3_SIZE]);

	Mat3(const Mat3& _other);
	Mat3(Mat3&& _other) noexcept;

	~Mat3();

public:
	static Mat3 CreateTransform(const Vec2& _trans, float _rot = 0.f, const Vec2* _scale = nullptr, float _xRot = 0.f, float _yRot = 0.f);

	static Mat3 CreateTranslation(const Vec2& _trans);
	static Mat3 CreateTranslation(const Vec3& _trans);

	static Mat3 CreateTranslation(float _x, float _y);
	static Mat3 CreateTranslation(float _x, float _y, float _z);

	static Mat3 CreateScale(const Vec2& _scale);
	static Mat3 CreateScale(const Vec3& _scale);

	static Mat3 CreateScale(float _x, float _y);
	static Mat3 CreateScale(float _x, float _y, float _z);

	static Mat3 CreateXRotation(float _rot);
	static Mat3 CreateYRotation(float _rot);
	static Mat3 CreateZRotation(float _rot);

	static Mat3 CreateEulerRotation(float _x, float _y, float _z);
	static Mat3 CreateEulerRotation(const Vec3& _euler);

	static Mat3 Identity();

public:
	void SetRotationX(float _rot);
	float GetRotationX() const;

	void SetRotationY(float _rot);
	float GetRotationY() const;

	void SetRotationZ(float _rot);
	float GetRotationZ() const;

	void SetTranslation(const Vec2& _trans);
	void Translate(const Vec2& _trans);
	Vec2 GetTranslation();

	void SetScale(const Vec2& _scale);
	Vec2 GetScale() const;

	Vec2 TransformPoint(const Vec2& _point) const;
	Vec2 TransformVector(const Vec2& _vec) const;

	Mat3 Transposed();

	string ToString() const;

public:
	Mat3 operator*(const Mat3& _rhs) const;
	Vec3 operator*(const Vec3& _rhs) const;

	bool operator==(const Mat3& _other) const;
	bool operator!=(const Mat3& _other) const;

	Mat3& operator=(const Mat3& _other);
	Mat3& operator=(Mat3&& _other) noexcept;

};