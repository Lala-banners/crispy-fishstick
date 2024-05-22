#include "Vec3.h"

#include "Spark/Maths/MathFunctions.h"

Vec3::Vec3()
	: x{ 0.f }, y{ 0.f }, z{ 0.f }
{
}

Vec3::Vec3(const float _scalar)
	: x{ _scalar }, y{ _scalar }, z{ _scalar }
{
}

Vec3::Vec3(const float _x, const float _y, const float _z)
	: x{ _x }, y{ _y }, z{ _z }
{
}

Vec3::Vec3(const initializer_list<float> _values)
{
	for (size_t i = 0; i < VEC_3_SIZE; ++i)
		data[i] = *(_values.begin() + i);
}

Vec3::Vec3(const Vector3 _vector)
	: x{ _vector.x }, y{ _vector.y }, z{ _vector.z }
{
}

Vec3::Vec3(const Vec3& _other)
	: x{ _other.x }, y{ _other.y }, z{ _other.z }
{
}

Vec3::Vec3(Vec3&& _other) noexcept
	: x{ _other.x }, y{ _other.y }, z{ _other.z }
{
	_other.x = 0.f;
	_other.y = 0.f;
	_other.z = 0.f;
}

Vec3::~Vec3() = default;

Vec3 Vec3::Add(const Vec3& _lhs, const Vec3& _rhs)
{
	return { _lhs.x + _rhs.x, _lhs.y + _rhs.y, _lhs.z + _rhs.z };
}

Vec3 Vec3::Subtract(const Vec3& _lhs, const Vec3& _rhs)
{
	return { _lhs.x - _rhs.x, _lhs.y - _rhs.y, _lhs.z - _rhs.z };
}

Vec3 Vec3::Scale(const Vec3& _lhs, const float _rhs)
{
	return { _lhs.x * _rhs, _lhs.y * _rhs, _lhs.z * _rhs };
}

Vec3 Vec3::Normalised(const Vec3& _vec)
{
	const float mag = _vec.Magnitude();

	return Compare(mag, 0.f) ?
		Vec3{ 0.f, 0.f, 0.f } :
		Vec3{ _vec.x / mag, _vec.y / mag, _vec.z / mag };
}

float Vec3::Distance(const Vec3& _a, const Vec3& _b)
{
	return (_a - _b).Magnitude();
}

float Vec3::Dot(const Vec3& _lhs, const Vec3& _rhs)
{
	return _lhs.x * _rhs.x + _lhs.y * _rhs.y + _lhs.z * _rhs.z;
}

Vec3 Vec3::Cross(const Vec3& _lhs, const Vec3& _rhs)
{
	return
	{
		_lhs.y * _rhs.z - _lhs.z * _rhs.y,
		_lhs.z * _rhs.x - _lhs.x * _rhs.z,
		_lhs.x * _rhs.y - _lhs.y * _rhs.x
	};
}

Vec3 Vec3::Lerp(const Vec3& _a, const Vec3& _b, float _t)
{
	return {};
}

float Vec3::Dot(const Vec3& _rhs) const
{
	return x * _rhs.x + y * _rhs.y + z * _rhs.z;
}

Vec3 Vec3::Cross(const Vec3& _rhs) const
{
	return
	{
		y * _rhs.z - z * _rhs.y,
		z * _rhs.x - x * _rhs.z,
		x * _rhs.y - y * _rhs.x
	};
}

float Vec3::Magnitude() const
{
	return sqrtf(x * x + y * y + z * z);
}

float Vec3::MagnitudeSqr() const
{
	return x * x + y * y + z * z;
}

void Vec3::Normalise()
{
	const float mag = Magnitude();

	if (Compare(mag, 0.f))
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
	}
	else
	{
		x /= mag;
		y /= mag;
		z /= mag;
	}
}

Vec3 Vec3::Normalised() const
{
	const float mag = Magnitude();

	return Compare(mag, 0.f) ?
		Vec3{ 0.f, 0.f, 0.f } :
		Vec3{ x / mag, y / mag, z / mag };
}

string Vec3::ToString() const
{
	return string("(") + std::to_string(x) +
		string(", ") + std::to_string(y) +
		string(", ") + std::to_string(z) +
		string(")");
}

Vec3::operator Vector3() const
{
	return { x, y, z };
}

bool Vec3::operator==(const Vec3& _other) const
{
	return Compare(x, _other.x) && Compare(y, _other.y) && Compare(z, _other.z);
}

bool Vec3::operator!=(const Vec3& _other) const
{
	return !(*this == _other);
}

Vec3 Vec3::operator-(const Vec3& _other) const
{
	return { x - _other.x, y - _other.y, z - _other.z };
}

Vec3& Vec3::operator-=(const Vec3& _other)
{
	x -= _other.x;
	y -= _other.y;
	z -= _other.z;

	return *this;
}

Vec3 Vec3::operator+(const Vec3& _other) const
{
	return { x + _other.x, y + _other.y, z + _other.z };
}

Vec3& Vec3::operator+=(const Vec3& _other)
{
	x += _other.x;
	y += _other.y;
	z += _other.z;

	return *this;
}

Vec3 Vec3::operator*(const float _other) const
{
	return { x * _other, y * _other, z * _other };
}

Vec3& Vec3::operator*=(const float _other)
{
	x *= _other;
	y *= _other;
	z *= _other;

	return *this;
}

Vec3& Vec3::operator=(const Vec3& _other)
{
	if (*this == _other)
		return *this;

	x = _other.x;
	y = _other.y;
	z = _other.z;

	return *this;
}

Vec3& Vec3::operator=(Vec3&& _other) noexcept
{
	if (*this == _other)
		return *this;

	x = _other.x;
	y = _other.y;
	z = _other.z;

	_other.x = 0.f;
	_other.y = 0.f;
	_other.z = 0.f;

	return *this;
}

Vec3 operator*(const float _lhs, const Vec3& _rhs)
{
	return { _rhs.x * _lhs, _rhs.y * _lhs, _rhs.z * _lhs };
}