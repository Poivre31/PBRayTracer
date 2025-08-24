#pragma once

#include <math.h>
#include <iostream>

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

	void Zero() {
		x = {};
		y = {};
		z = {};
	}

	float Norm() const {
		return sqrt(x * x + y * y + z * z);
	}

	float Norm2() const {
		return x * x + y * y + z * z;
	}

	void Normalize() {
		float r = Norm();
		if (r == 0) return;
		x /= r;
		y /= r;
		z /= r;
	}

	float Sum() const {
		return x + y + z;
	}

	void Print() const {
		std::printf("x: %.12f, y: %.12f, z: %.12f \n", x, y, z);
	}

	template<typename U>
	operator Vec3<U>() {
		return Vec3<U>(U(x), U(y), U(z));
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
		z /= a;
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
};

template<typename T>
inline Vec3<T> exp(const Vec3<T>& u) {
	return Vec3<T>(exp(u.x), exp(u.y), exp(u.z));
}

template<typename T>
inline Vec3<T> log(const Vec3<T>& u) {
	return Vec3<T>(log(u.x), log(u.y), log(u.z));
}

template<typename T>
inline Vec3<T> exp2(const Vec3<T>& u) {
	return Vec3<T>(exp2(u.x), exp2(u.y), exp2(u.z));
}

template<typename T>
inline Vec3<T> log2(const Vec3<T>& u) {
	return Vec3<T>(log2(u.x), log2(u.y), log2(u.z));
}

template<typename T>
inline Vec3<T> exp10(const Vec3<T>& u) {
	return Vec3<T>(exp10(u.x), exp10(u.y), exp10(u.z));
}

template<typename T>
inline Vec3<T> log10(const Vec3<T>& u) {
	return Vec3<T>(log10(u.x), log10(u.y), log10(u.z));
}

template<typename T>
inline Vec3<T> pow(const Vec3<T>& u, const Vec3<T>& v) {
	return Vec3<T>(pow(u.x, v.x), pow(u.y, v.y), pow(u.z, v.z));
}

template<typename T>
inline Vec3<T> pow(const Vec3<T>& u, float a) {
	return Vec3<T>(pow(u.x, a), pow(u.y, a), pow(u.z, a));
}

template<typename T>
inline Vec3<T> sqrt(const Vec3<T>& u) {
	return Vec3<T>(sqrt(u.x), sqrt(u.y), sqrt(u.z));
}

template<typename T>
inline Vec3<T> sin(const Vec3<T>& u) {
	return Vec3<T>(sin(u.x), sin(u.y), sin(u.z));
}

template<typename T>
inline Vec3<T> cos(const Vec3<T>& u) {
	return Vec3<T>(cos(u.x), cos(u.y), cos(u.z));
}

template<typename T>
inline Vec3<T> tan(const Vec3<T>& u) {
	return Vec3<T>(tan(u.x), tan(u.y), tan(u.z));
}

template<typename T>
inline Vec3<T> asin(const Vec3<T>& u) {
	return Vec3<T>(asin(u.x), asin(u.y), asin(u.z));
}

template<typename T>
inline Vec3<T> acos(const Vec3<T>& u) {
	return Vec3<T>(acos(u.x), acos(u.y), acos(u.z));
}

template<typename T>
inline Vec3<T> atan(const Vec3<T>& u) {
	return Vec3<T>(atan(u.x), atan(u.y), atan(u.z));
}

template<typename T>
inline Vec3<T> sinh(const Vec3<T>& u) {
	return Vec3<T>(sinh(u.x), sinh(u.y), sinh(u.z));
}

template<typename T>
inline Vec3<T> cosh(const Vec3<T>& u) {
	return Vec3<T>(cosh(u.x), cosh(u.y), cosh(u.z));
}

template<typename T>
inline Vec3<T> tanh(const Vec3<T>& u) {
	return Vec3<T>(tanh(u.x), tanh(u.y), tanh(u.z));
}

template<typename T>
inline Vec3<T> min(const Vec3<T>& u, const Vec3<T>& v) {
	return Vec3<T>(min(u.x, v.x), min(u.y, v.y), min(u.z, v.z));
}

template<typename T>
inline Vec3<T> min(const Vec3<T>& u, float a) {
	return Vec3<T>(min(u.x, a), min(u.y, a), min(u.z, a));
}

template<typename T>
inline Vec3<T> max(const Vec3<T>& u, const Vec3<T>& v) {
	return Vec3<T>(max(u.x, v.x), max(u.y, v.y), max(u.z, v.z));
}

template<typename T>
inline Vec3<T> max(const Vec3<T>& u, float a) {
	return Vec3<T>(max(u.x, a), max(u.y, a), max(u.z, a));
}

template<typename T>
inline Vec3<T> abs(const Vec3<T>& u) {
	return Vec3<T>(abs(u.x), abs(u.y), abs(u.z));
}

template<typename T>
inline Vec3<T> cross(const Vec3<T>& u, const Vec3<T>& v) {
	Vec3 out{};
	out.x = u.y * v.z - v.y * u.z;
	out.y = u.z * v.x - v.z * u.x;
	out.z = u.x * v.y - v.x * u.y;
	return out;
}

template<typename T>
inline float dot(const Vec3<T>& a, const Vec3<T>& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

template<typename T>
inline Vec3<T> rotX(const Vec3<T>& u, float alpha) {
	Vec3 v{};
	float cosa = cos(alpha);
	float sina = sin(alpha);
	v.x = u.x;
	v.y = cosa * u.y - sina * u.z;
	v.z = sina * u.y + cosa * u.z;
	return v;
}

template<typename T>
inline Vec3<T> rotY(const Vec3<T>& u, float alpha) {
	Vec3 v{};
	float cosa = cos(alpha);
	float sina = sin(alpha);
	v.x = cosa * u.x + sina * u.z;
	v.y = u.y;
	v.z = -sina * u.x + cosa * u.z;
	return v;
}

template<typename T>
inline Vec3<T> rotZ(const Vec3<T>& u, float alpha) {
	Vec3<T> v{};
	float cosa = cos(alpha);
	float sina = sin(alpha);
	v.x = cosa * u.x - sina * u.y;
	v.y = sina * u.x + cosa * u.y;
	v.z = u.z;
	return v;
}

template<typename T>
inline Vec3<T> sph2cart(Vec3<T> rho_theta_phi) {
	Vec3 xyz{};
	xyz.x = rho_theta_phi.x * sin(rho_theta_phi.y) * cos(rho_theta_phi.z);
	xyz.y = rho_theta_phi.x * sin(rho_theta_phi.y) * sin(rho_theta_phi.z);
	xyz.z = rho_theta_phi.x * cos(rho_theta_phi.y);
	return xyz;
}

template<typename T>
inline Vec3<T> cart2sph(Vec3<T> xyz) {
	Vec3 rho_theta_phi{};
	rho_theta_phi.x = xyz.Norm();
	if (rho_theta_phi.x == 0) return rho_theta_phi;
	rho_theta_phi.y = acos(xyz.z / rho_theta_phi.x);
	rho_theta_phi.z = atan2(xyz.y, xyz.x);
	return rho_theta_phi;
}