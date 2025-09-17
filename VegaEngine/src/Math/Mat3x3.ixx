export module Math:Mat3x3;
import :Vec3;
import :Vec3Math;

export namespace Vega::Math {
	/// 3x3 matrix of doubles. 
	/// Default constructor returns the identity matrix.
	/// Matrix/Matrix and Matrix/Vector multiplication using Mul(A,B). 
	class Mat3x3 {
	public:
		double a1 = 0, a2 = 0, a3 = 0;
		double b1 = 0, b2 = 0, b3 = 0;
		double c1 = 0, c2 = 0, c3 = 0;
		Vec3<double&> L1;
		Vec3<double&> L2;
		Vec3<double&> L3;
		Vec3<double&> C1;
		Vec3<double&> C2;
		Vec3<double&> C3;

		Mat3x3()
			: L1(a1, a2, a3), L2(b1, b2, b3), L3(c1, c2, c3),
			C1(a1, b1, c1), C2(a2, b2, c2), C3(a3, b3, c3)
		{
			a1 = 1.;
			a2 = 0.;
			a3 = 0.;
			b1 = 0.;
			b2 = 1.;
			b3 = 0.;
			c1 = 0.;
			c2 = 0.;
			c3 = 1.;
		}

		Mat3x3(double x)
			: L1(a1, a2, a3), L2(b1, b2, b3), L3(c1, c2, c3),
			C1(a1, b1, c1), C2(a2, b2, c2), C3(a3, b3, c3)
		{
			a1 = x;
			a2 = x;
			a3 = x;
			b1 = x;
			b2 = x;
			b3 = x;
			c1 = x;
			c2 = x;
			c3 = x;
		}

		Mat3x3(const Mat3x3& M)
			: L1(a1, a2, a3), L2(b1, b2, b3), L3(c1, c2, c3),
			C1(a1, b1, c1), C2(a2, b2, c2), C3(a3, b3, c3)
		{
			a1 = M.a1;
			a2 = M.a2;
			a3 = M.a3;
			b1 = M.b1;
			b2 = M.b2;
			b3 = M.b3;
			c1 = M.c1;
			c2 = M.c2;
			c3 = M.c3;
		}

		Mat3x3(double a1_, double a2_, double a3_, double b1_, double b2_, double b3_, double c1_, double c2_, double c3_)
			: a1(a1_), a2(a2_), a3(a3_), b1(b1_), b2(b2_), b3(b3_), c1(c1_), c2(c2_), c3(c3_),
			L1(a1, a2, a3), L2(b1, b2, b3), L3(c1, c2, c3),
			C1(a1, b1, c1), C2(a2, b2, c2), C3(a3, b3, c3)
		{
		}

		Mat3x3(Vec3<double> l1, Vec3<double> l2, Vec3<double> l3, bool rowMajor = true) :
			L1(a1, a2, a3), L2(b1, b2, b3), L3(c1, c2, c3),
			C1(a1, b1, c1), C2(a2, b2, c2), C3(a3, b3, c3)
		{
			if (rowMajor) {
				a1 = l1.x;
				a2 = l1.y;
				a3 = l1.z;
				b1 = l2.x;
				b2 = l2.y;
				b3 = l2.z;
				c1 = l3.x;
				c2 = l3.y;
				c3 = l3.z;
			}
			else {
				a1 = l1.x;
				a2 = l2.x;
				a3 = l3.x;
				b1 = l1.y;
				b2 = l2.y;
				b3 = l3.y;
				c1 = l1.z;
				c2 = l2.z;
				c3 = l3.z;
			}
		}

		Mat3x3 T() {
			Mat3x3 M = *this;
			M.Transpose();
			return M;
		}

		void Transpose() {
			std::swap(a2, b1);
			std::swap(a3, c1);
			std::swap(b3, c2);
		}

		Mat3x3& ShiftLines(bool down) {
			if (down) {
				std::swap(c1, b1);
				std::swap(b1, a1);
				std::swap(c2, b2);
				std::swap(b2, a2);
				std::swap(c3, b3);
				std::swap(b3, a3);
			}
			else {
				std::swap(b1, a1);
				std::swap(c1, b1);
				std::swap(b2, a2);
				std::swap(c2, b2);
				std::swap(b3, a3);
				std::swap(c3, b3);
			}
			return *this;
		}

		double Det() const {
			double det = a1 * (b2 * c3 - b3 * c2);
			det -= a2 * (b1 * c3 - b3 * c1);
			det += a3 * (b1 * c2 - b2 * c1);
			return det;
		}

		/// <summary>
		/// Element wise multiplication of A and B
		/// </summary>
		friend Mat3x3 operator*(Mat3x3 A, const Mat3x3& B) {
			Mat3x3 M;
			M.a1 = A.a1 * B.a1;
			M.a2 = A.a2 * B.a2;
			M.a3 = A.a3 * B.a3;
			M.b1 = A.b1 * B.b1;
			M.b2 = A.b2 * B.b2;
			M.b3 = A.b3 * B.b3;
			M.c1 = A.c1 * B.c1;
			M.c2 = A.c2 * B.c2;
			M.c3 = A.c3 * B.c3;
			return M;
		}

		friend Mat3x3 operator*(float a, const Mat3x3& B) {
			Mat3x3 M;
			M.a1 = a * B.a1;
			M.a2 = a * B.a2;
			M.a3 = a * B.a3;
			M.b1 = a * B.b1;
			M.b2 = a * B.b2;
			M.b3 = a * B.b3;
			M.c1 = a * B.c1;
			M.c2 = a * B.c2;
			M.c3 = a * B.c3;
			return M;
		}

		Mat3x3& operator=(const Mat3x3& M) {
			a1 = M.a1;
			a2 = M.a2;
			a3 = M.a3;
			b1 = M.b1;
			b2 = M.b2;
			b3 = M.b3;
			c1 = M.c1;
			c2 = M.c2;
			c3 = M.c3;
			return *this;
		}

		void Print() {
			std::println("[ {}, {}, {} ]", a1, a2, a3);
			std::println("[ {}, {}, {} ]", b1, b2, b3);
			std::println("[ {}, {}, {} ]\n", c1, c2, c3);
		}

		static Mat3x3 RotationX(double theta) {
			double cosTheta = std::cos(theta);
			double sinTheta = std::sin(theta);
			return Mat3x3(
				1., 0., 0.,
				0., cosTheta, -sinTheta,
				0., sinTheta, cosTheta
			);
		}

		static Mat3x3 RotationY(double theta) {
			double cosTheta = std::cos(theta);
			double sinTheta = std::sin(theta);
			return Mat3x3(
				cosTheta, 0., sinTheta,
				0., 1., 0.,
				-sinTheta, 0., cosTheta
			);
		}

		static Mat3x3 RotationZ(double theta) {
			double cosTheta = std::cos(theta);
			double sinTheta = std::sin(theta);
			return Mat3x3(
				cosTheta, -sinTheta, 0.,
				sinTheta, cosTheta, 0.,
				0., 0., 1.
			);
		}
	};

	inline Vec3<double> Mul(const Mat3x3& M, const Vec3<double>& u) {
		Vec3<double> v;
		v.x = dot(M.L1, u);
		v.y = dot(M.L2, u);
		v.z = dot(M.L3, u);
		return v;
	}

	inline Mat3x3 Mul(const Mat3x3& A, const Mat3x3& B) {
		Mat3x3 M;
		M.a1 = dot(A.L1, B.C1);
		M.a2 = dot(A.L1, B.C2);
		M.a3 = dot(A.L1, B.C3);
		M.b1 = dot(A.L2, B.C1);
		M.b2 = dot(A.L2, B.C2);
		M.b3 = dot(A.L2, B.C3);
		M.c1 = dot(A.L3, B.C1);
		M.c2 = dot(A.L3, B.C2);
		M.c3 = dot(A.L3, B.C3);
		return M;
	}

	inline void Mul(const Mat3x3& A, const Mat3x3& B, Mat3x3& M) {
		if (!(&M != &A && &B != &M)) {
			std::cout << "Matrix multiplication aliasing: use temp output matrix or M = Mul(A,B) instead";
			exit(-1);
		}
		M.a1 = dot(A.L1, B.C1);
		M.a2 = dot(A.L1, B.C2);
		M.a3 = dot(A.L1, B.C3);
		M.b1 = dot(A.L2, B.C1);
		M.b2 = dot(A.L2, B.C2);
		M.b3 = dot(A.L2, B.C3);
		M.c1 = dot(A.L3, B.C1);
		M.c2 = dot(A.L3, B.C2);
		M.c3 = dot(A.L3, B.C3);
	}


	class Mat3x3f {
	public:
		float a1 = 0, a2 = 0, a3 = 0;
		float b1 = 0, b2 = 0, b3 = 0;
		float c1 = 0, c2 = 0, c3 = 0;

		Mat3x3f(const Mat3x3& M) {
			a1 = (float)M.a1;
			a2 = (float)M.a2;
			a3 = (float)M.a3;
			b1 = (float)M.b1;
			b2 = (float)M.b2;
			b3 = (float)M.b3;
			c1 = (float)M.c1;
			c2 = (float)M.c2;
			c3 = (float)M.c3;
		}

		Mat3x3f(Mat3x3& M) {
			a1 = (float)M.a1;
			a2 = (float)M.a2;
			a3 = (float)M.a3;
			b1 = (float)M.b1;
			b2 = (float)M.b2;
			b3 = (float)M.b3;
			c1 = (float)M.c1;
			c2 = (float)M.c2;
			c3 = (float)M.c3;
		}

		float* GetAdress() {
			return &a1;
		}
	};
}