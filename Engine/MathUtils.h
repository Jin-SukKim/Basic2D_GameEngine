#pragma once
#include <intrin.h>
 
struct Vector2D;

struct MathUtils
{
	static constexpr float PI = { 3.14159265358979323846f };
	static constexpr float TwoPI = { 2.f * PI };
	static constexpr float HalfPI = { 1.57079632679f };
	static constexpr float InvPI = { 0.31830988618f };

	// �𸮾� ���� �ڵ忡�� ������. ��� �������� ���� ( 1 / sqrt(x) )
	FORCEINLINE static float InvSqrt(float InFloat)
	{
		/*
			�������͸� ���� �� ũ��� �����ִ� ������ �ִµ�
			�̶� �Ǽ� �������� sqrt(x) ����� �����ɸ���.

			�׷��� 1/sqrt(x)�� ���� ���ؾ��ϴ� ��� �� ȿ������ ����� �ʿ��ϴ�.
			InvSqrt �˰����� ����, ������ ��Ʈ ���길 �̿��� 1 / sqrt(x)�� 1% �̳��� ������ ������ �����ش�.
		*/

		// Performs two passes of Newton-Raphson iteration on the hardware estimate
		//    v^-0.5 = x
		// => x^2 = v^-1
		// => 1/(x^2) = v
		// => F(x) = x^-2 - v
		//    F'(x) = -2x^-3

		//    x1 = x0 - F(x0)/F'(x0)
		// => x1 = x0 + 0.5 * (x0^-2 - Vec) * x0^3
		// => x1 = x0 + 0.5 * (x0 - Vec * x0^3)
		// => x1 = x0 + x0 * (0.5 - 0.5 * Vec * x0^2)
		//
		// This final form has one more operation than the legacy factorization (X1 = 0.5*X0*(3-(Y*X0)*X0)
		// but retains better accuracy (namely InvSqrt(1) = 1 exactly).

		const __m128 fOneHalf = _mm_set_ss(0.5f);
		__m128 Y0, X0, X1, X2, FOver2;
		float temp;

		Y0 = _mm_set_ss(InFloat);
		X0 = _mm_rsqrt_ss(Y0);	// 1/sqrt estimate (12 bits)
		FOver2 = _mm_mul_ss(Y0, fOneHalf);

		// 1st Newton-Raphson iteration
		X1 = _mm_mul_ss(X0, X0);
		X1 = _mm_sub_ss(fOneHalf, _mm_mul_ss(FOver2, X1));
		X1 = _mm_add_ss(X0, _mm_mul_ss(X0, X1));

		// 2nd Newton-Raphson iteration
		X2 = _mm_mul_ss(X1, X1);
		X2 = _mm_sub_ss(fOneHalf, _mm_mul_ss(FOver2, X2));
		X2 = _mm_add_ss(X1, _mm_mul_ss(X1, X2));

		_mm_store_ss(&temp, X2);
		return temp;
	}

	// H = | x1 - x1 | + | y2 - y1 |, ���� + ���� �̵�
	static int32 Manhattan(const Vector2D& a, const Vector2D& b);

	// H = sqrt( (x2 - x1)^2 + (y2 - y1)^2 ), ���� + ���� + �밢��
	static int32 Euclidean(const Vector2D& a, const Vector2D& b);

	static float LinearInterpolation(const float& a, const float& b, const float& t);
	static Vector2D LinearInterpolation(const Vector2D& src, const Vector2D& dest, const float& t);

	static Vector2D floor(const Vector2D& v);
};

