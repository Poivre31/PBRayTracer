#pragma once

#include <math.h>
#include <iostream>
#include <span>
#include <concepts>
#include <type_traits>

#define M_PI 3.14159265358979

template<typename T>
class Vec2 {
public:
	T x{};
	T y{};

	Vec2() = default;

	Vec2(T a) : x(a), y(a) {}

	Vec2(T x, T y, T z) : x(x), y(y) {}

	Vec2(const Vec2& ref) : x(ref.x), y(ref.y) {}

	template<typename U>
	Vec2(const Vec2<U>& ref) : x(T(ref.x)), y(T(ref.y)) {}

	template<typename U>
	Vec2& operator=(const Vec2<U>& v) {
		x = T(v.x);
		y = T(v.y);
		return *this;
	}

	void Zero() {
		x = {};
		y = {};
	}

	double Norm() const {
		return sqrt(x * x + y * y);
	}

	double Norm2() const {
		return x * x + y * y;
	}

	void Normalize() {
		double r = x * x + y * y;
		if (r == 0) return;
		r = 1. / sqrt(r);
		x *= r;
		y *= r;
	}

	double Sum() const {
		return x + y;
	}

	void Print() const {
		std::printf("x: %.4f, y: %.4f \n", x, y);
	}

	void Print(const char* message) const {
		std::printf("%s x: %.4f, y: %.4f \n", message, x, y);
	}

	Vec2<bool> IsNegative() {
		return Vec2<bool>(x < 0., y < 0.);
	}

	Vec2<bool> Equals(Vec2<T> ref) {
		return Vec2<bool>(x == ref.x, y == ref.y);
	}

	Vec2<bool> Less(Vec2<T> ref) {
		return Vec2<bool>(x < ref.x, y < ref.y);
	}

	Vec2<bool> Less(T ref) {
		return Vec2<bool>(x < ref, y < ref);
	}

	Vec2<bool> LessEq(Vec2<T> ref) {
		return Vec2<bool>(x <= ref.x, y <= ref.y);
	}

	Vec2<bool> Greater(Vec2<T> ref) {
		return Vec2<bool>(x > ref.x, y > ref.y);
	}

	Vec2<bool> GreaterEq(Vec2<T> ref) {
		return Vec2<bool>(x >= ref.x, y >= ref.y);
	}

	bool operator==(const Vec2& v) const {
		return (x == v.x && y == v.y);
	}

	template<typename U>
	operator Vec2<U>() {
		return Vec2<U>(U(x), U(y));
	}

	template<typename U>
	friend Vec2 operator*(U a, const Vec2& v) {
		Vec2 out;
		out.x = v.x * a;
		out.y = v.y * a;
		return out;
	}

	template<typename U>
	friend Vec2 operator*(const Vec2& v, U a) {
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

	template<typename U>
	Vec2& operator*=(U a) {
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

	template<typename U>
	friend Vec2 operator/(const Vec2& u, U a) {
		Vec2 out;
		double aInv = 1. / a;
		out.x = u.x * aInv;
		out.y = u.y * aInv;
		return out;
	}

	Vec2& operator/=(const Vec2& v) {
		x /= v.x;
		y /= v.y;
		return *this;
	}

	template<typename U>
	Vec2& operator/=(U a) {
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