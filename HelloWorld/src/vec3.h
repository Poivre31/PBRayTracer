#pragma once

#include <iostream>
#include <math.h>
#include <numbers>

using std::numbers::pi;

struct Vec3 {
	float x, y, z;

	Vec3() {
		x = .0f;
		y = .0f;
		z = .0f;
	}

	Vec3(float a) : x(a), y(a), z(a) {};

	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	Vec3(const Vec3& ref) {
		x = ref.x;
		y = ref.y;
		z = ref.z;
	}

	friend Vec3 operator*(float a, const Vec3& v) {
		Vec3 out;
		out.x = v.x * a;
		out.y = v.y * a;
		out.z = v.z * a;
		return out;
	}

	friend Vec3 operator*(const Vec3& v, float a) {
		Vec3 out;
		out.x = v.x * a;
		out.y = v.y * a;
		out.z = v.z * a;
		return out;
	}

	Vec3& operator*=(const Vec3& v) {
		this->x *= v.x;
		this->y *= v.y;
		this->z *= v.z;
		return *this;
	}

	friend Vec3 operator^(const Vec3& u, const Vec3& v) {
		Vec3 out;
		out.x = u.y * v.z - v.y * u.z;
		out.y = u.z * v.x - v.z * u.x;
		out.z = u.x * v.y - v.x * u.y;
		return out;
	}

	friend Vec3 operator+(const Vec3& u, const Vec3& v) {
		Vec3 out;
		out.x = v.x + u.x;
		out.y = v.y + u.y;
		out.z = v.z + u.z;
		return out;
	}

	Vec3& operator+=(const Vec3& v) {
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		return *this;
	}

	friend Vec3 operator-(const Vec3& u, const Vec3& v) {
		Vec3 out;
		out.x = u.x - v.x;
		out.y = u.y - v.y;
		out.z = u.z - v.z;
		return out;
	}

	Vec3 operator-() const {
		Vec3 out;
		out.x = -x;
		out.y = -y;
		out.z = -z;
		return out;
	}
	Vec3& operator-=(const Vec3& v) {
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
		return *this;
	}
	void Set(float X, float Y, float Z) {
		x = X;
		y = Y;
		z = Z;
	}

	void zero() {
		x = 0;
		y = 0;
		z = 0;
	}

	void Normalize() {
		float r = sqrt(x * x + y * y + z * z);
		if (r == 0) return;
		x /= r;
		y /= r;
		z /= r;
	}

	float Sum() const {
		return x + y + z;
	}

	void sphToCart() {
		float rho = x;
		float theta = y;
		float phi = z;

		x = rho * sin(theta) * cos(phi);
		y = rho * sin(theta) * sin(phi);
		z = rho * cos(theta);
	}

	void cartToSph() {
		float rho = sqrt(x * x + y * y + z * z);
		if (rho == 0) return;
		float theta = acos(z / rho);
		float phi = atan2(y, x);
		if (phi < 0) phi += 2.f * pi;
		Set(rho, theta, phi);
	}

	float Norm2() const {
		return x * x + y * y + z * z;
	}

	void print() const {
		std::cout << "x: " << x << ", y: " << y << ", z: " << z << "\n";
	}
};

inline float dot(const Vec3& a, const Vec3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vec3 rotX(const Vec3& u, float alpha) {
	Vec3 v = Vec3();
	float cosa = cos(alpha);
	float sina = sin(alpha);
	v.x = u.x;
	v.y = cosa * u.y - sina * u.z;
	v.z = sina * u.y + cosa * u.z;
	return v;
}

inline Vec3 rotY(const Vec3& u, float alpha) {
	Vec3 v = Vec3();
	float cosa = cos(alpha);
	float sina = sin(alpha);
	v.x = cosa * u.x + sina * u.z;
	v.y = u.y;
	v.z = -sina * u.x + cosa * u.z;
	return v;
}

inline Vec3 rotZ(const Vec3& u, float alpha) {
	Vec3 v = Vec3();
	float cosa = cos(alpha);
	float sina = sin(alpha);
	v.x = cosa * u.x - sina * u.y;
	v.y = sina * u.x + cosa * u.y;
	v.z = u.z;
	return v;
}

inline Vec3 sph2cart(Vec3 rtp) {
	Vec3 xyz;
	xyz.x = rtp.x * sin(rtp.y) * cos(rtp.z);
	xyz.y = rtp.x * sin(rtp.y) * sin(rtp.z);
	xyz.z = rtp.x * cos(rtp.y);
	return xyz;
}

inline Vec3 cart2sph(Vec3 xyz) {
	Vec3 rtp;
	rtp.x = sqrt(xyz.x * xyz.x + xyz.y * xyz.y + xyz.z * xyz.z);
	if (rtp.x == 0) return rtp;
	rtp.y = acos(xyz.z / rtp.x);
	rtp.z = atan2(xyz.y, xyz.x);
	return rtp;
}

