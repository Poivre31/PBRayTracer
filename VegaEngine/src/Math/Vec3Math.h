#pragma once
#include "Vec3.h"

template<typename T>
inline T sign(T a) {
	if (a == 0) return 0;
	else return (a > 0) * 2. - 1.;
}

template<typename T>
inline Vec3<T> sign(const Vec3<T>& u) {
	return Vec3<T>(sign(u.x), sign(u.y), sign(u.z));
}

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

template<typename T, typename U>
inline Vec3<T> pow(const Vec3<T>& u, U a) {
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

//template<typename T>
//inline Vec3<T> min(const Vec3<T>& u, const Vec3<T>& v) {
//	return Vec3<T>(min(u.x, v.x), min(u.y, v.y), min(u.z, v.z));
//}
//
//template<typename T, typename U >
//inline Vec3<T> min(const Vec3<T>& u, U a) {
//	return Vec3<T>(min(u.x, a), min(u.y, a), min(u.z, a));
//}
//
//template<typename T>
//inline Vec3<T> max(const Vec3<T>& u, const Vec3<T>& v) {
//	return Vec3<T>(max(u.x, v.x), max(u.y, v.y), max(u.z, v.z));
//}
//
//template<typename T, typename U >
//inline Vec3<T> max(const Vec3<T>& u, U a) {
//	return Vec3<T>(max(u.x, a), max(u.y, a), max(u.z, a));
//}

template<typename T>
inline Vec3<T> abs(const Vec3<T>& u) {
	return Vec3<T>(abs(u.x), abs(u.y), abs(u.z));
}

template<typename T>
inline Vec3<T> cross(const Vec3<T>& u, const Vec3<T>& v) {
	T x = u.y * v.z - v.y * u.z;
	T y = u.z * v.x - v.z * u.x;
	T z = u.x * v.y - v.x * u.y;
	return Vec3(x, y, z);
}

template<typename T, typename U>
inline double dot(const Vec3<T>& a, const Vec3<U>& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

template<typename T, typename U>
inline Vec3<T> rotX(const Vec3<T>& u, U alpha) {
	U cosa = cos(alpha);
	U sina = sin(alpha);
	T x = u.x;
	T y = cosa * u.y - sina * u.z;
	T z = sina * u.y + cosa * u.z;
	return Vec3(x, y, z);
}

template<typename T, typename U>
inline Vec3<T> rotY(const Vec3<T>& u, U alpha) {
	U cosa = cos(alpha);
	U sina = sin(alpha);
	T x = cosa * u.x + sina * u.z;
	T y = u.y;
	T z = -sina * u.x + cosa * u.z;
	return Vec3(x, y, z);
}

template<typename T, typename U>
inline Vec3<T> rotZ(const Vec3<T>& u, U alpha) {
	U cosa = cos(alpha);
	U sina = sin(alpha);
	T x = cosa * u.x - sina * u.y;
	T y = sina * u.x + cosa * u.y;
	T z = u.z;
	return Vec3(x, y, z);
}

inline Vec3<double> sph2cart(Vec3<double> rho_theta_phi) {
	double x = rho_theta_phi.x * sin(rho_theta_phi.y) * cos(rho_theta_phi.z);
	double y = rho_theta_phi.x * sin(rho_theta_phi.y) * sin(rho_theta_phi.z);
	double z = rho_theta_phi.x * cos(rho_theta_phi.y);
	return Vec3(x, y, z);
}

inline Vec3<double> sph2cartr1(Vec3<double> rho_theta_phi) {
	double x = sin(rho_theta_phi.y) * cos(rho_theta_phi.z);
	double y = sin(rho_theta_phi.y) * sin(rho_theta_phi.z);
	double z = cos(rho_theta_phi.y);
	return Vec3(x, y, z);
}

inline Vec3<float> sph2cart(Vec3<float> rho_theta_phi) {
	float x = rho_theta_phi.x * sin(rho_theta_phi.y) * cos(rho_theta_phi.z);
	float y = rho_theta_phi.x * sin(rho_theta_phi.y) * sin(rho_theta_phi.z);
	float z = rho_theta_phi.x * cos(rho_theta_phi.y);
	return Vec3(x, y, z);
}

inline Vec3<float> sph2cartr1(Vec3<float> rho_theta_phi) {
	float x = sin(rho_theta_phi.y) * cos(rho_theta_phi.z);
	float y = sin(rho_theta_phi.y) * sin(rho_theta_phi.z);
	float z = cos(rho_theta_phi.y);
	return Vec3(x, y, z);
}

inline Vec3<double> cart2sph(Vec3<double> xyz) {
	Vec3<double> rho_theta_phi = Vec3(1.);
	rho_theta_phi.x = xyz.Norm();
	if (rho_theta_phi.x == 0) return rho_theta_phi;
	rho_theta_phi.y = acos(xyz.z / rho_theta_phi.x);
	rho_theta_phi.z = atan2(xyz.y, xyz.x);
	return rho_theta_phi;
}

inline Vec3<double> cart2sphr1(Vec3<double> xyz) {
	Vec3<double> rho_theta_phi = Vec3(1.);
	rho_theta_phi.y = acos(xyz.z);
	rho_theta_phi.z = atan2(xyz.y, xyz.x);
	return rho_theta_phi;
}

inline Vec3<float> cart2sph(Vec3<float> xyz) {
	Vec3<float> rho_theta_phi = Vec3(1.f);
	rho_theta_phi.x = (float)xyz.Norm();
	if (rho_theta_phi.x == 0) return rho_theta_phi;
	rho_theta_phi.y = acos(xyz.z / rho_theta_phi.x);
	rho_theta_phi.z = atan2(xyz.y, xyz.x);
	return rho_theta_phi;
}

inline Vec3<float> cart2sphr1(Vec3<float> xyz) {
	Vec3<float> rho_theta_phi = Vec3(1.f);
	rho_theta_phi.y = acos(xyz.z);
	rho_theta_phi.z = atan2(xyz.y, xyz.x);
	return rho_theta_phi;
}

inline Vec3<bool> Not(Vec3<bool> vec) {
	return Vec3((bool)(1 - vec.x), (bool)(1 - vec.y), (bool)(1 - vec.z));
}

inline Vec3<bool> And(Vec3<bool> a, Vec3<bool> b) {
	return Vec3(a.x && b.x, a.y && b.y, a.z && b.z);
}

inline Vec3<bool> Or(Vec3<bool> a, Vec3<bool> b) {
	return Vec3(a.x || b.x, a.y || b.y, a.z || b.z);
}

inline Vec3<bool> Xor(Vec3<bool> a, Vec3<bool> b) {
	return Not(Vec3(a.x == b.x, a.y == b.y, a.z == b.z));
}

inline Vec3<bool> NOr(Vec3<bool> a, Vec3<bool> b) {
	return Not(Or(a, b));
}

inline Vec3<bool> NAnd(Vec3<bool> a, Vec3<bool> b) {
	return Not(And(a, b));
}

inline Vec3<bool> NXor(Vec3<bool> a, Vec3<bool> b) {
	return Not(Xor(a, b));
}