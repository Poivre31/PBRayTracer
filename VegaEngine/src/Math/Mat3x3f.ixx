export module Math:Mat3x3f;
import :Mat3x3;

export namespace Vega::Math {
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