#pragma once
#include <random>
#include "Vec3.h"

namespace Vega {

	class Random {
	public:
		static float RandFloat(float a, float b) {
			return (b - a) * float(rand()) / RAND_MAX + a;
		}
		static double RandDouble(double a, double b) {
			return (b - a) * double(rand()) / RAND_MAX + a;
		}

		static Vec3<float> RandVec3f(float a, float b) {
			return Vec3(RandFloat(a, b), RandFloat(a, b), RandFloat(a, b));
		}
		static Vec3<double> RandVec3d(double a, double b) {
			return Vec3(RandDouble(a, b), RandDouble(a, b), RandDouble(a, b));
		}

		static int RandInt(int a, int b) {
			return a + rand() % (b - a);
		}

	private:
	};

}