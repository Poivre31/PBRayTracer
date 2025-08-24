#pragma once

#include <math.h>
#include <iostream>

#define M_PI 3.14159265358979

template<typename T>
class Vec2 {
public:
	T x{};
	T y{};

	Vec2() = default;

	Vec2(T a) : x(a), y(a) {}

	Vec2(T x, T y) : x(x), y(y) {}

	Vec2(const Vec2& ref) {
		x = ref.x;
		y = ref.y;
	}

	void Zero() {
		x = {};
		y = {};
	}

	float Norm() const {
		return sqrt(x * x + y * y);
	}

	float Norm2() const {
		return x * x + y * y;
	}

	void Normalize() {
		float r = Norm();
		if (r == 0) return;
		x /= r;
		y /= r;
	}

	float Sum() const {
		return x + y;
	}

	void Print() const {
		std::printf("x: %.12f, y: %.12f \n", x, y);
	}

	template<typename U>
	operator Vec2<U>() {
		return Vec2<U>(U(x), U(y));
	}

	friend Vec2 operator*(float a, const Vec2& v) {
		Vec2 out;
		out.x = v.x * a;
		out.y = v.y * a;
		return out;
	}

	friend Vec2 operator*(const Vec2& v, float a) {
		Vec2 out;
		out.x = v.x * a;
		out.y = v.y * a;
		return out;
	}

	friend Vec2 operator*(const Vec2& u, const Vec2& v) {
		Vec2 out;
		out.x = u.x * v.x;
		out.y = u.y * v.y;
		return out;
	}

	Vec2& operator*=(float a) {
		x *= a;
		y *= a;
		return *this;
	}

	Vec2& operator*=(const Vec2& u) {
		x *= u.x;
		y *= u.y;
		return *this;
	}

	friend Vec2 operator/(const Vec2& u, const Vec2& v) {
		Vec2 out;
		out.x = u.x / v.x;
		out.y = u.y / v.y;
		return out;
	}

	friend Vec2 operator/(const Vec2& u, float a) {
		Vec2 out;
		float aInv = 1 / a;
		out.x = u.x * aInv;
		out.y = u.y * aInv;
		return out;
	}

	Vec2& operator/=(const Vec2& v) {
		x /= v.x;
		y /= v.y;
		return *this;
	}

	Vec2& operator/=(float a) {
		x /= a;
		y /= a;
		return *this;
	}

	friend Vec2 operator+(const Vec2& u, const Vec2& v) {
		Vec2 out;
		out.x = u.x + v.x;
		out.y = u.y + v.y;
		return out;
	}

	Vec2& operator+=(const Vec2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	friend Vec2 operator-(const Vec2& u, const Vec2& v) {
		Vec2 out;
		out.x = u.x - v.x;
		out.y = u.y - v.y;
		return out;
	}

	Vec2& operator-=(const Vec2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vec2 operator-() const {
		Vec2 out;
		out.x = -x;
		out.y = -y;
		return out;
	}
};

template<typename T>
inline Vec2<T> exp(const Vec2<T>& u) {
	return Vec2<T>(exp(u.x), exp(u.y));
}

template<typename T>
inline Vec2<T> log(const Vec2<T>& u) {
	return Vec2<T>(log(u.x), log(u.y));
}

template<typename T>
inline Vec2<T> exp2(const Vec2<T>& u) {
	return Vec2<T>(exp2(u.x), exp2(u.y));
}

template<typename T>
inline Vec2<T> log2(const Vec2<T>& u) {
	return Vec2<T>(log2(u.x), log2(u.y));
}

template<typename T>
inline Vec2<T> exp10(const Vec2<T>& u) {
	return Vec2<T>(exp10(u.x), exp10(u.y));
}

template<typename T>
inline Vec2<T> log10(const Vec2<T>& u) {
	return Vec2<T>(log10(u.x), log10(u.y));
}

template<typename T>
inline Vec2<T> pow(const Vec2<T>& u, const Vec2<T>& v) {
	return Vec2<T>(pow(u.x, v.x), pow(u.y, v.y));
}

template<typename T>
inline Vec2<T> pow(const Vec2<T>& u, float a) {
	return Vec2<T>(pow(u.x, a), pow(u.y, a));
}

template<typename T>
inline Vec2<T> sqrt(const Vec2<T>& u) {
	return Vec2<T>(sqrt(u.x), sqrt(u.y));
}

template<typename T>
inline Vec2<T> sin(const Vec2<T>& u) {
	return Vec2<T>(sin(u.x), sin(u.y));
}

template<typename T>
inline Vec2<T> cos(const Vec2<T>& u) {
	return Vec2<T>(cos(u.x), cos(u.y));
}

template<typename T>
inline Vec2<T> tan(const Vec2<T>& u) {
	return Vec2<T>(tan(u.x), tan(u.y));
}

template<typename T>
inline Vec2<T> asin(const Vec2<T>& u) {
	return Vec2<T>(asin(u.x), asin(u.y));
}

template<typename T>
inline Vec2<T> acos(const Vec2<T>& u) {
	return Vec2<T>(acos(u.x), acos(u.y));
}

template<typename T>
inline Vec2<T> atan(const Vec2<T>& u) {
	return Vec2<T>(atan(u.x), atan(u.y));
}

template<typename T>
inline Vec2<T> sinh(const Vec2<T>& u) {
	return Vec2<T>(sinh(u.x), sinh(u.y));
}

template<typename T>
inline Vec2<T> cosh(const Vec2<T>& u) {
	return Vec2<T>(cosh(u.x), cosh(u.y));
}

template<typename T>
inline Vec2<T> tanh(const Vec2<T>& u) {
	return Vec2<T>(tanh(u.x), tanh(u.y));
}

template<typename T>
inline Vec2<T> min(const Vec2<T>& u, const Vec2<T>& v) {
	return Vec2<T>(min(u.x, v.x), min(u.y, v.y));
}

template<typename T>
inline Vec2<T> min(const Vec2<T>& u, float a) {
	return Vec2<T>(min(u.x, a), min(u.y, a));
}

template<typename T>
inline Vec2<T> max(const Vec2<T>& u, const Vec2<T>& v) {
	return Vec2<T>(max(u.x, v.x), max(u.y, v.y));
}

template<typename T>
inline Vec2<T> max(const Vec2<T>& u, float a) {
	return Vec2<T>(max(u.x, a), max(u.y, a));
}

template<typename T>
inline Vec2<T> abs(const Vec2<T>& u) {
	return Vec2<T>(abs(u.x), abs(u.y));
}

template<typename T>
inline float dot(const Vec2<T>& a, const Vec2<T>& b) {
	return a.x * b.x + a.y * b.y;
}