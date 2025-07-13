#pragma once
#include <chrono>

using namespace std::chrono;

class Timer
{
	steady_clock::time_point time;

public:
	Timer() {
		time = high_resolution_clock::now();
	}

	double EllapsedTimeS() const {
		auto t2 = high_resolution_clock::now();
		return .000000001 * duration_cast<nanoseconds>(t2 - time).count();
	}
	double EllapsedTimeMS() const {
		auto t2 = high_resolution_clock::now();
		return .000001 * duration_cast<nanoseconds>(t2 - time).count();
	}
	double EllapsedTimeUS() const {
		auto t2 = high_resolution_clock::now();
		return .001 * duration_cast<nanoseconds>(t2 - time).count();
	}
	Timer* Reset() {
		time = high_resolution_clock::now();
		return this;
	}
	Timer* PrintEllapsedTime() {
		printf("Ellapsed time: %.1f ms\n", EllapsedTimeUS() / 1000);
		return this;
	}
	Timer* PrintEllapsedTime(const char* str) {
		printf("%s: %.1f ms\n", str, EllapsedTimeUS() / 1000);
		return this;
	}
};