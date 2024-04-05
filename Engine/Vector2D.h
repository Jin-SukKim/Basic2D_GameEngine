#pragma once

struct Vector2D
{
	Vector2D() : X(0.f), Y(0.f) {}
	Vector2D(float X, float Y) : X(X), Y(Y) {}
	Vector2D(int X, int Y) : X(static_cast<float>(X)), Y(static_cast<float>(Y)) {}
	Vector2D(POINT pt) : X((float)pt.x), Y((float)pt.y) {}
	Vector2D(const Vector2D& other) : X(other.X), Y(other.Y) {}
	Vector2D(Vector2D&& other) noexcept : X(other.X), Y(other.Y) {
		other.X = 0.f;
		other.Y = 0.f;
	}

	Vector2D& operator=(const Vector2D& other) {
		if (&other == this) // 같으면
			return *this;

		X = other.X;
		Y = other.Y;

		return *this;
	}

	Vector2D& operator=(Vector2D&& other) noexcept {
		if (&other == this)
			return *this;

		X = other.X;
		Y = other.Y;

		other.X = 0.f;
		other.Y = 0.f;

		return *this;
	}

	float operator[](int8 indeX) {
		assert(indeX < Dimension); // Dimension보다 크면 assert error
		return Scalars[indeX];
	}

	Vector2D operator-() const {
		return Vector2D(-X, -Y);
	}

	Vector2D operator+(const Vector2D& other) const {
		return Vector2D(X + other.X, Y + other.Y);
	}

	Vector2D operator-(const Vector2D& other) const {
		return Vector2D(X - other.X, Y - other.Y);
	}

	Vector2D operator*(const Vector2D& other) const {
		return Vector2D(X * other.X, Y * other.Y);
	}

	Vector2D operator*(const float& scalar) const {
		return Vector2D(X * scalar, Y * scalar);
	}

	Vector2D& operator+=(const Vector2D& other) {
		*this = *this + other;
		return *this;
	}

	Vector2D& operator-=(const Vector2D& other) {
		*this = *this - other;
		return *this;
	}
	Vector2D& operator*=(const Vector2D& other) {
		*this = *this * other;
		return *this;
	}

	Vector2D& operator*=(const float& scalar) {
		*this = *this * scalar;
		return *this;
	}

	bool operator==(const Vector2D& other) const {
		return X == other.X && Y == other.Y;
	}
	bool operator!=(const Vector2D& other) const {
		return !(*this == other);
	}

	bool operator>(const Vector2D& other) const {
		if (X != other.X)
			return X > other.X;
		return Y > other.Y;
	}

	bool operator<(const Vector2D& other) const {
		if (X != other.X)
			return X < other.X;
		return Y < other.Y;
	}


	// 단순 계산만 할땐 sqrt를 굳이 안해도 된다. (계산량 아끼기)
	float LengthSquared() {
		return X * X + Y * Y;
	}

	// 길이
	float Length() {
		return std::sqrtf(LengthSquared());
	}

	Vector2D GetNormalize() {
		float lengthSq = LengthSquared();
		if (lengthSq == 1.f)
			return *this;
		else if (lengthSq == 0.f)
			return Vector2D::Zero;

		float invLength = MathUtils::InvSqrt(lengthSq); // 1 / sqrt(X)
		return Vector2D(X, Y) * invLength; // sqrt(X)로 나누는 것과 같다.
	}

	void Normalize() {
		*this = GetNormalize();
	}

	// 단위벡터인 경우 cos(theta)를 구할 수 있다.
	float Dot(const Vector2D& other) {
		return X * other.X + Y * other.Y;
	}

	// 단위벡터인 경우 sin(theta)를 구할 수 있다.
	float Cross(const Vector2D& other)
	{
		return X * other.Y - Y * other.X;
	}

	static const Vector2D Zero;
	static const Vector2D UnitX;
	static const Vector2D UnitY;
	static const Vector2D One;
	static const int8 Dimension = 2;

	union {
		struct {
			float X, Y;
		};
		std::array<float, Dimension> Scalars = { 0.f, 0.f };
	};
};

// float * Vector2D가 가능해진다.
extern Vector2D operator*(const float& scalar, const Vector2D& v);
