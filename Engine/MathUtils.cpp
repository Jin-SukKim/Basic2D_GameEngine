#include "pch.h"
#include "MathUtils.h"

int32 MathUtils::Manhattan(const Vector2D& a, const Vector2D& b)
{
	return static_cast<int32>(std::abs(b.X - a.X) + std::abs(b.Y - a.Y));
}

int32 MathUtils::Euclidean(const Vector2D& a, const Vector2D& b)
{
	return static_cast<int32>(std::sqrt((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y)));
}

float MathUtils::LinearInterpolation(const float& a, const float& b, const float& t)
{
	return (1.f - t) * a + t * b;
}

Vector2D MathUtils::LinearInterpolation(const Vector2D& src, const Vector2D& dest, const float& t)
{
	return (1.f - t) * src + t * dest;
}