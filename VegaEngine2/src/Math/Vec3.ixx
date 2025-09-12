export module Math:Vec3;
import std;

export namespace Vega::Math {
		template<typename T>
			class Vec3 {
			public:
				T x{};
				T y{};
				T z{};

				Vec3() = default;

				Vec3(T a) : x(a), y(a), z(a) {}

				Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

				Vec3(const Vec3& ref) : x(ref.x), y(ref.y), z(ref.z) {}

				template<typename U>
				Vec3(const Vec3<U>& ref) : x(T(ref.x)), y(T(ref.y)), z(T(ref.z)) {}

				template<typename U>
				Vec3& operator=(const Vec3<U>& v) {
					x = T(v.x);
					y = T(v.y);
					z = T(v.z);
					return *this;
				}

				void Zero() {
					x = {};
					y = {};
					z = {};
				}

				double Norm() const {
					return std::sqrt(x * x + y * y + z * z);
				}

				double Norm2() const {
					return x * x + y * y + z * z;
				}

				void Normalize() {
					double r = x * x + y * y + z * z;
					if (r == 0) return;
					r = 1. / sqrt(r);
					x *= r;
					y *= r;
					z *= r;
				}

				double Sum() const {
					return x + y + z;
				}

				void Print() const {
					std::printf("x: %.4f, y: %.4f, z: %.4f \n", x, y, z);
				}

				void Print(const char* message) const {
					std::printf("%s x: %.4f, y: %.4f, z: %.4f \n", message, x, y, z);
				}

				static Vec3 X() {
					return Vec3(1, 0, 0);
				}

				static Vec3 Y() {
					return Vec3(0, 1, 0);
				}

				static Vec3 Z() {
					return Vec3(0, 0, 1);
				}

				Vec3<bool> IsNegative() {
					return Vec3<bool>(x < 0., y < 0., z < 0.);
				}

				Vec3<bool> Equals(Vec3<T> ref) {
					return Vec3<bool>(x == ref.x, y == ref.y, z == ref.z);
				}

				Vec3<bool> Less(Vec3<T> ref) {
					return Vec3<bool>(x < ref.x, y < ref.y, z < ref.z);
				}

				Vec3<bool> Less(T ref) {
					return Vec3<bool>(x < ref, y < ref, z < ref);
				}

				Vec3<bool> LessEq(Vec3<T> ref) {
					return Vec3<bool>(x <= ref.x, y <= ref.y, z <= ref.z);
				}

				Vec3<bool> Greater(Vec3<T> ref) {
					return Vec3<bool>(x > ref.x, y > ref.y, z > ref.z);
				}

				Vec3<bool> GreaterEq(Vec3<T> ref) {
					return Vec3<bool>(x >= ref.x, y >= ref.y, z >= ref.z);
				}

				bool operator==(const Vec3& v) const {
					return (x == v.x && y == v.y && z == v.z);
				}

				template<typename U>
				operator Vec3<U>() {
					return Vec3<U>(U(x), U(y), U(z));
				}

				template<typename U>
				operator std::span<U, 3>() {
					U out[3] = { U(x), U(y), U(z) };
					return std::span<U, 3>(out);
				}

				template<typename U>
				friend Vec3 operator*(U a, const Vec3& v) {
					Vec3 out;
					out.x = v.x * a;
					out.y = v.y * a;
					out.z = v.z * a;
					return out;
				}

				template<typename U>
				friend Vec3 operator*(const Vec3& v, U a) {
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

				template<typename U>
				Vec3& operator*=(U a) {
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

				template<typename U>
				friend Vec3 operator/(const Vec3& u, U a) {
					Vec3 out;
					double aInv = 1. / a;
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

				template<typename U>
				Vec3& operator/=(U a) {
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
	}
