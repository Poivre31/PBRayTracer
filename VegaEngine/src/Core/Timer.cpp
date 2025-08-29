#include "Timer.h"


namespace Vega {

	double Timer::GetTimeS() {
		return double((steady_clock::now().time_since_epoch() - _epoch).count()) / 1000000000;
	}

	double Timer::GetTimeMS() {
		return double((steady_clock::now().time_since_epoch() - _epoch).count()) / 1000000;
	}

	double Timer::GetTimeUS() {
		return double((steady_clock::now().time_since_epoch() - _epoch).count()) / 1000;
	}

	double Timer::GetTimeSinceStartup() {
		return GetTimeS() - _startTime;
	}

}