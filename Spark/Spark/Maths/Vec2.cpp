#include "Vec2.h"

#include "Spark/Maths/MathFunctions.h"

Vec2 Vec2::one = Vec2(1.f, 1.f);
Vec2 Vec2::zero = Vec2(0.f, 0.f);
Vec2 Vec2::half = Vec2(.5f, .5f);
Vec2 Vec2::up = Vec2(0.f, 1.f);
Vec2 Vec2::down = Vec2(0.f, -1.f);
Vec2 Vec2::left = Vec2(-1.f, 0.f);
Vec2 Vec2::right = Vec2(1.f, 0.f);

Vec2::Vec2()
	: x{ 0.f }, y{ 0.f }
{
}

Vec2::Vec2(const float _scalar)
	: x{ _scalar }, y{ _scalar }
{
}

Vec2::Vec2(const float _x, const float _y)
	: x{ _x }, y{ _y }
{
}

Vec2::Vec2(const initializer_list<float> _values)
{
	for (size_t i = 0; i < VEC_2_SIZE; ++i)
		data[i] = *(_values.begin() + i);
}

Vec2::Vec2(const Vector2 _pos)
	: x{ _pos.x }, y{ _pos.y }
{
}

Vec2::Vec2(const Vec2& _other)
	: x{ _other.x }, y{ _other.y }
{
}

Vec2::Vec2(Vec2&& _other) noexcept
	: x{ _other.x }, y{ _other.y }
{
	_other.x = 0.f;
	_other.y = 0.f;
}

Vec2::~Vec2() = default;

Vec2 Vec2::Add(const Vec2& _lhs, const Vec2& _rhs)
{
	return { _lhs.x + _rhs.x, _lhs.y + _rhs.y };
}

Vec2 Vec2::Subtract(const Vec2& _lhs, const Vec2& _rhs)
{
	return { _lhs.x - _rhs.x, _lhs.y - _rhs.y };
}

Vec2 Vec2::Scale(const Vec2& _lhs, const float _rhs)
{
	return { _lhs.x * _rhs, _lhs.y * _rhs };
}

Vec2 Vec2::Normalised(const Vec2& _vec)
{
	const float mag = _vec.Magnitude();

	if (Compare(mag, 0.f))
	{
		return Vec2{ 0.f, 0.f };
	}
	else
	{
		return Vec2{ _vec.x / mag, _vec.y / mag };
	}
}

float Vec2::Distance(const Vec2& _a, const Vec2& _b)
{
	return (_a - _b).Magnitude();
}

float Vec2::Dot(const Vec2& _lhs, const Vec2& _rhs)
{
	return _lhs.x * _rhs.x + _lhs.y * _rhs.y;
}

Vec2 Vec2::Lerp(const Vec2& _a, const Vec2& _b, float _t)
{
	return {};
}

Vec2 Vec2::CreateRotationVector(const float _radians)
{
	return { cosf(_radians), sinf(_radians) };
}

float Vec2::Dot(const Vec2& _rhs) const
{
	return x * _rhs.x + y * _rhs.y;
}

float Vec2::Magnitude() const
{
	return sqrtf(x * x + y * y);
}

float Vec2::MagnitudeSqr() const
{
	return x * x + y * y;
}

void Vec2::Normalise()
{
	const float mag = Magnitude();

	if (Compare(mag, 0.f))
	{
		x = 0.f;
		y = 0.f;
	}
	else
	{
		x /= mag;
		y /= mag;
	}
}

Vec2 Vec2::Normalised() const
{
	const float mag = Magnitude();

	return Compare(mag, 0.f) ? Vec2{ 0.f, 0.f } : Vec2{ x / mag, y / mag };
}

float Vec2::Rotation() const
{
	return atan2f(y, x);
}

void Vec2::Rotate(const float _amount)
{
	const float xRotated = x * cosf(_amount) - y * sinf(_amount);
	const float yRotated = x * sinf(_amount) + y * cosf(_amount);

	x = xRotated;
	y = yRotated;
}

void Vec2::RotateAround(const Vec2& _pivot, const float _amount)
{
	x -= _pivot.x;
	y -= _pivot.y;

	Rotate(_amount);

	x += _pivot.x;
	y += _pivot.y;
}

string Vec2::ToString() const
{
	return string("(") + std::to_string(x) + string(", ") + std::to_string(y) + string(")");
}

Vec2::operator Vector2() const
{
	return { x, y };
}

bool Vec2::operator==(const Vec2& _other) const
{
	return Compare(x, _other.x) && Compare(y, _other.y);
}

bool Vec2::operator!=(const Vec2& _other) const
{
	return !(*this == _other);
}

Vec2 Vec2::operator-(const Vec2& _other) const
{
	return { x - _other.x, y - _other.y };
}

Vec2& Vec2::operator-=(const Vec2& _other)
{
	x -= _other.x;
	y -= _other.y;

	return *this;
}

Vec2 Vec2::operator+(const Vec2& _other) const
{
	return { x + _other.x, y + _other.y };
}

Vec2& Vec2::operator+=(const Vec2& _other)
{
	x += _other.x;
	y += _other.y;

	return *this;
}

Vec2 Vec2::operator*(const float _other) const
{
	return { x * _other, y * _other };
}

Vec2& Vec2::operator*=(const float _other)
{
	x *= _other;
	y *= _other;

	return *this;
}

Vec2 Vec2::operator*(const Vec2& _other) const
{
	return { x * _other.x, y * _other.y };
}

Vec2& Vec2::operator*=(const Vec2& _other)
{
	x *= _other.x;
	y *= _other.y;

	return *this;
}

Vec2& Vec2::operator=(const Vec2& _other)
{
	if (*this == _other)
		return *this;

	x = _other.x;
	y = _other.y;

	return *this;
}

Vec2& Vec2::operator=(Vec2&& _other) noexcept
{
	if (*this == _other)
		return *this;

	x = _other.x;
	y = _other.y;

	_other.x = 0.f;
	_other.y = 0.f;

	return *this;
}

Vec2& Vec2::operator=(const Vector2 _other)
{
	x = _other.x;
	y = _other.y;

	return *this;
}

Vec2 operator*(const float _lhs, const Vec2& _rhs)
{
	return { _rhs.x * _lhs, _rhs.y * _lhs };
}