#pragma once

struct Vector2D
{
	Vector2D() : x(0.f), y(0.f) {}
	Vector2D(float x, float y) : x(x), y(y) {}
	Vector2D(POINT pt) : x((float)pt.x), y((float)pt.y) {}

	Vector2D(const Vector2D& other) : x(other.x), y(other.y) {}
	Vector2D(Vector2D&& other) noexcept : x(other.x), y(other.y) {
		other.x = 0.f;
		other.y = 0.f;
	}

	Vector2D& operator=(const Vector2D& other) {
		if (&other == this) // ������
			return *this;

		x = other.x;
		y = other.y;

		return *this;
	}

	Vector2D& operator=(Vector2D&& other) noexcept {
		if (&other == this)
			return *this;

		x = other.x;
		y = other.y;

		other.x = 0.f;
		other.y = 0.f;

		return *this;
	}

	float operator[](int8 index) {
		assert(index < Dimension); // Dimension���� ũ�� assert error
		return Scalars[index];
	}

	Vector2D operator-() const {
		return Vector2D(-x, -y);
	}

	Vector2D operator+(const Vector2D& other) const {
		return Vector2D(x + other.x, y + other.y);
	}

	Vector2D operator-(const Vector2D& other) const {
		return Vector2D(x - other.x, y - other.y);
	}

	Vector2D operator*(const Vector2D& other) const {
		return Vector2D(x * other.x, y * other.y);
	}

	Vector2D operator*(const float& scalar) const {
		return Vector2D(x * scalar, y * scalar);
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
		return x == other.x && y == other.y;
	}
	bool operator!=(const Vector2D& other) const {
		return !(*this == other);
	}

	bool operator>(const Vector2D& other) const {
		if (x != other.x)
			return x > other.x;
		return y > other.y;
	}

	bool operator<(const Vector2D& other) const {
		if (x != other.x)
			return x < other.x;
		return y < other.y;
	}


	// �ܼ� ��길 �Ҷ� sqrt�� ���� ���ص� �ȴ�. (��귮 �Ƴ���)
	float LengthSquared() {
		return x * x + y * y;
	}

	// ����
	float Length() {
		return std::sqrtf(LengthSquared());
	}

	Vector2D GetNormalize() {
		float lengthSq = LengthSquared();
		if (lengthSq == 1.f)
			return *this;
		else if (lengthSq == 0.f)
			return Vector2D::Zero;

		float invLength = MathUtils::InvSqrt(lengthSq); // 1 / sqrt(x)
		return Vector2D(x, y) * invLength; // sqrt(x)�� ������ �Ͱ� ����.
	}

	void Normalize() {
		*this = GetNormalize();
	}

	// ���������� ��� cos(theta)�� ���� �� �ִ�.
	float Dot(const Vector2D& other) {
		return x * other.x + y * other.y;
	}

	// ���������� ��� sin(theta)�� ���� �� �ִ�.
	float Cross(const Vector2D& other)
	{
		return x * other.y - y * other.x;
	}

	static const Vector2D Zero;
	static const Vector2D UnitX;
	static const Vector2D UnitY;
	static const Vector2D One;
	static const int8 Dimension = 2;

	union {
		struct {
			float x, y;
		};
		std::array<float, Dimension> Scalars = { 0.f, 0.f };
	};
};

// float * Vector2D�� ����������.
extern Vector2D operator*(const float& scalar, const Vector2D& v);
