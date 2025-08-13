#pragma once
#include <algorithm>

constexpr float M_PI = 3.141592653589793f;

inline float randF(float a, float b) {
	float out = a + (b - a) / RAND_MAX * rand();
	return out;
}

inline int clamp(int n, int low, int high) {
	if (n >= high) return high;
	if (n <= low) return low;
	return n;
}

inline float min(float a, float b) {
	return a > b ? b : a;
}

inline float max(float a, float b) {
	return a < b ? b : a;
}