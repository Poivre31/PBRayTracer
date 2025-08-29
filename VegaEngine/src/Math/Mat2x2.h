#pragma once
#include "Vec2.h"

class Mat2x2 {
public:
	double a0, a1;
	Vec2<double&> C1;

	Mat2x2() = default;
	Mat2x2(Vec2<double> l1, Vec2<double> l2, bool rowMajor = true) : C1(a0,a1) {
		if (true) {
			a0 = l1.x;
			a1 = l1.y;
		}
	}

	void Print() {
		printf("[ %.4f, %.4f ]\n", a0, a1);
		//printf("[ %.4f, %.4f ]\n", b0, b1);
	}

};