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