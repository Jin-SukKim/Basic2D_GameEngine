#include "pch.h"
#include "Vector2D.h"

const Vector2D Vector2D::Zero(0.f, 0.f);
const Vector2D Vector2D::UnitX(1.f, 0.f);
const Vector2D Vector2D::UnitY(0.f, 1.f);
const Vector2D Vector2D::One(1.f, 1.f);

extern Vector2D operator*(const float& scalar, const Vector2D& v) {
	return Vector2D(scalar * v.x, scalar * v.y);
}
