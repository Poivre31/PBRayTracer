export module Math:Vec3Math;
import :Vec3;
import std;

export namespace Vega::Math {

	template<typename T>
	T sign(T a) {
		if (a == 0) return 0;
		else return (a > 0) * 2. - 1.;
	}

	template<typename T>
	Vec3<T> sign(const Vec3<T>& u) {
		return Vec3<T>(sign(u.x), sign(u.y), sign(u.z));
	}

	template<typename T>
	Vec3<T> exp(const Vec3<T>& u) {
		return Vec3<T>(std::exp(u.x), std::exp(u.y), std::exp(u.z));
	}

	template<typename T>
	Vec3<T> log(const Vec3<T>& u) {
		return Vec3<T>(std::log(u.x), std::log(u.y), std::log(u.z));
	}

	template<typename T>
	Vec3<T> exp2(const Vec3<T>& u) {
		return Vec3<T>(std::exp2(u.x), std::exp2(u.y), std::exp2(u.z));
	}

	template<typename T>
	Vec3<T> log2(const Vec3<T>& u) {
		return Vec3<T>(std::log2(u.x), std::log2(u.y), std::log2(u.z));
	}

	template<typename T>
	Vec3<T> pow(const Vec3<T>& u, const Vec3<T>& v) {
		return Vec3<T>(std::pow(u.x, v.x), std::pow(u.y, v.y), std::pow(u.z, v.z));
	}

	template<typename T, typename U>
	Vec3<T> pow(const Vec3<T>& u, U a) {
		return Vec3<T>(std::pow(u.x, a), std::pow(u.y, a), std::pow(u.z, a));
	}

	template<typename T>
	Vec3<T> sqrt(const Vec3<T>& u) {
		return Vec3<T>(std::sqrt(u.x), std::sqrt(u.y), std::sqrt(u.z));
	}

	template<typename T>
	Vec3<T> sin(const Vec3<T>& u) {
		return Vec3<T>(std::sin(u.x), std::sin(u.y), std::sin(u.z));
	}

	template<typename T>
	Vec3<T> cos(const Vec3<T>& u) {
		return Vec3<T>(std::cos(u.x), std::cos(u.y), std::cos(u.z));
	}

	template<typename T>
	Vec3<T> tan(const Vec3<T>& u) {
		return Vec3<T>(std::tan(u.x), std::tan(u.y), std::tan(u.z));
	}

	template<typename T>
	Vec3<T> asin(const Vec3<T>& u) {
		return Vec3<T>(std::asin(u.x), std::asin(u.y), std::asin(u.z));
	}

	template<typename T>
	Vec3<T> acos(const Vec3<T>& u) {
		return Vec3<T>(std::acos(u.x), std::acos(u.y), std::acos(u.z));
	}

	template<typename T>
	Vec3<T> atan(const Vec3<T>& u) {
		return Vec3<T>(std::atan(u.x), std::atan(u.y), std::atan(u.z));
	}

	template<typename T>
	Vec3<T> sinh(const Vec3<T>& u) {
		return Vec3<T>(std::sinh(u.x), std::sinh(u.y), std::sinh(u.z));
	}

	template<typename T>
	Vec3<T> cosh(const Vec3<T>& u) {
		return Vec3<T>(std::cosh(u.x), std::cosh(u.y), std::cosh(u.z));
	}

	template<typename T>
	Vec3<T> tanh(const Vec3<T>& u) {
		return Vec3<T>(std::tanh(u.x), std::tanh(u.y), std::tanh(u.z));
	}

	//template<typename T>
	//Vec3<T> min(const Vec3<T>& u, const Vec3<T>& v) {
	//	return Vec3<T>(min(u.x, v.x), min(u.y, v.y), min(u.z, v.z));
	//}
	//
	//template<typename T, typename U >
	//Vec3<T> min(const Vec3<T>& u, U a) {
	//	return Vec3<T>(min(u.x, a), min(u.y, a), min(u.z, a));
	//}
	//
	//template<typename T>
	//Vec3<T> max(const Vec3<T>& u, const Vec3<T>& v) {
	//	return Vec3<T>(max(u.x, v.x), max(u.y, v.y), max(u.z, v.z));
	//}
	//
	//template<typename T, typename U >
	//Vec3<T> max(const Vec3<T>& u, U a) {
	//	return Vec3<T>(max(u.x, a), max(u.y, a), max(u.z, a));
	//}

	template<typename T>
	Vec3<T> abs(const Vec3<T>& u) {
		return Vec3<T>(std::abs(u.x), std::abs(u.y), std::abs(u.z));
	}

	template<typename T>
	Vec3<T> cross(const Vec3<T>& u, const Vec3<T>& v) {
		T x = u.y * v.z - v.y * u.z;
		T y = u.z * v.x - v.z * u.x;
		T z = u.x * v.y - v.x * u.y;
		return Vec3(x, y, z);
	}

	template<typename T, typename U>
	double dot(const Vec3<T>& a, const Vec3<U>& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	template<typename T, typename U>
	Vec3<T> rotX(const Vec3<T>& u, U alpha) {
		U cosa = std::cos(alpha);
		U sina = std::sin(alpha);
		T x = u.x;
		T y = cosa * u.y - sina * u.z;
		T z = sina * u.y + cosa * u.z;
		return Vec3(x, y, z);
	}

	template<typename T, typename U>
	Vec3<T> rotY(const Vec3<T>& u, U alpha) {
		U cosa = std::cos(alpha);
		U sina = std::sin(alpha);
		T x = cosa * u.x + sina * u.z;
		T y = u.y;
		T z = -sina * u.x + cosa * u.z;
		return Vec3(x, y, z);
	}

	template<typename T, typename U>
	Vec3<T> rotZ(const Vec3<T>& u, U alpha) {
		U cosa = std::cos(alpha);
		U sina = std::sin(alpha);
		T x = cosa * u.x - sina * u.y;
		T y = sina * u.x + cosa * u.y;
		T z = u.z;
		return Vec3(x, y, z);
	}

	Vec3<double> sph2cart(Vec3<double> rho_theta_phi) {
		double x = rho_theta_phi.x * std::sin(rho_theta_phi.y) * std::cos(rho_theta_phi.z);
		double y = rho_theta_phi.x * std::sin(rho_theta_phi.y) * std::sin(rho_theta_phi.z);
		double z = rho_theta_phi.x * std::cos(rho_theta_phi.y);
		return Vec3(x, y, z);
	}

	Vec3<double> sph2cartr1(Vec3<double> rho_theta_phi) {
		double x = std::sin(rho_theta_phi.y) * std::cos(rho_theta_phi.z);
		double y = std::sin(rho_theta_phi.y) * std::sin(rho_theta_phi.z);
		double z = std::cos(rho_theta_phi.y);
		return Vec3(x, y, z);
	}

	Vec3<float> sph2cart(Vec3<float> rho_theta_phi) {
		float x = rho_theta_phi.x * std::sin(rho_theta_phi.y) * std::cos(rho_theta_phi.z);
		float y = rho_theta_phi.x * std::sin(rho_theta_phi.y) * std::sin(rho_theta_phi.z);
		float z = rho_theta_phi.x * std::cos(rho_theta_phi.y);
		return Vec3(x, y, z);
	}

	Vec3<float> sph2cartr1(Vec3<float> rho_theta_phi) {
		float x = std::sin(rho_theta_phi.y) * std::cos(rho_theta_phi.z);
		float y = std::sin(rho_theta_phi.y) * std::sin(rho_theta_phi.z);
		float z = std::cos(rho_theta_phi.y);
		return Vec3(x, y, z);
	}

	Vec3<double> cart2sph(Vec3<double> xyz) {
		Vec3<double> rho_theta_phi = Vec3(1.);
		rho_theta_phi.x = xyz.Norm();
		if (rho_theta_phi.x == 0) return rho_theta_phi;
		rho_theta_phi.y = std::acos(xyz.z / rho_theta_phi.x);
		rho_theta_phi.z = atan2(xyz.y, xyz.x);
		return rho_theta_phi;
	}

	Vec3<double> cart2sphr1(Vec3<double> xyz) {
		Vec3<double> rho_theta_phi = Vec3(1.);
		rho_theta_phi.y = std::acos(xyz.z);
		rho_theta_phi.z = std::atan2(xyz.y, xyz.x);
		return rho_theta_phi;
	}

	Vec3<float> cart2sph(Vec3<float> xyz) {
		Vec3<float> rho_theta_phi = Vec3(1.f);
		rho_theta_phi.x = (float)xyz.Norm();
		if (rho_theta_phi.x == 0) return rho_theta_phi;
		rho_theta_phi.y = std::acos(xyz.z / rho_theta_phi.x);
		rho_theta_phi.z = std::atan2(xyz.y, xyz.x);
		return rho_theta_phi;
	}

	Vec3<float> cart2sphr1(Vec3<float> xyz) {
		Vec3<float> rho_theta_phi = Vec3(1.f);
		rho_theta_phi.y = std::acos(xyz.z);
		rho_theta_phi.z = std::atan2(xyz.y, xyz.x);
		return rho_theta_phi;
	}

	Vec3<bool> Not(Vec3<bool> vec) {
		return Vec3((bool)(1 - vec.x), (bool)(1 - vec.y), (bool)(1 - vec.z));
	}

	Vec3<bool> And(Vec3<bool> a, Vec3<bool> b) {
		return Vec3(a.x && b.x, a.y && b.y, a.z && b.z);
	}

	Vec3<bool> Or(Vec3<bool> a, Vec3<bool> b) {
		return Vec3(a.x || b.x, a.y || b.y, a.z || b.z);
	}

	Vec3<bool> Xor(Vec3<bool> a, Vec3<bool> b) {
		return Not(Vec3(a.x == b.x, a.y == b.y, a.z == b.z));
	}

	Vec3<bool> NOr(Vec3<bool> a, Vec3<bool> b) {
		return Not(Or(a, b));
	}

	Vec3<bool> NAnd(Vec3<bool> a, Vec3<bool> b) {
		return Not(And(a, b));
	}

	Vec3<bool> NXor(Vec3<bool> a, Vec3<bool> b) {
		return Not(Xor(a, b));
	}
}