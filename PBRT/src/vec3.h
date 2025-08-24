#pragma once

#include <iostream>
#include <math.h>
#include <numbers>

#define M_PI 3.14159265358979

template<typename T>
class Vec3 {
public:
	T x{};
	T y{};
	T z{};

	Vec3() = default;

	Vec3(T a) : x(a), y(a), z(a) {}
	Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

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

	friend Vec3 operator*(const Vec3& u, const Vec3& v) {
		Vec3 out;
		out.x = u.x * v.x;
		out.y = u.y * v.y;
		out.z = u.z * v.z;
		return out;
	}

	Vec3& operator*=(float a) {
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	Vec3& operator*=(const Vec3& u) {
		x *= u.x;
		y *= u.y;
		z *= u.z;
		return *this;
	}

	friend Vec3 operator/(const Vec3& u, const Vec3& v) {
		Vec3 out;
		out.x = u.x / v.x;
		out.y = u.y / v.y;
		out.z = u.z / v.z;
		return out;
	}

	friend Vec3 operator/(const Vec3& u, float a) {
		Vec3 out;
		float aInv = 1 / a;
		out.x = u.x * aInv;
		out.y = u.y * aInv;
		out.z = u.z * aInv;
		return out;
	}

	Vec3& operator/=(const Vec3& v) {
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	Vec3& operator/=(float a) {
		x /= a;
		y /= a;
		z /= az;
		return *this;
	}

	friend Vec3 operator+(const Vec3& u, const Vec3& v) {
		Vec3 out;
		out.x = u.x + v.x;
		out.y = u.y + v.y;
		out.z = u.z + v.z;
		return out;
	}

	Vec3& operator+=(const Vec3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	friend Vec3 operator-(const Vec3& u, const Vec3& v) {
		Vec3 out;
		out.x = u.x - v.x;
		out.y = u.y - v.y;
		out.z = u.z - v.z;
		return out;
	}

	Vec3& operator-=(const Vec3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vec3 operator-() const {
		Vec3 out;
		out.x = -x;
		out.y = -y;
		out.z = -z;
		return out;
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


inline Vec3 Cross(const Vec3& u, const Vec3& v) {
	Vec3 out;
	out.x = u.y * v.z - v.y * u.z;
	out.y = u.z * v.x - v.z * u.x;
	out.z = u.x * v.y - v.x * u.y;
	return out;
}

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

