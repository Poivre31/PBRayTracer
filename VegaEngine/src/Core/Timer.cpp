#include "Timer.h"

namespace Vega {

	double Timer::GetTimeS() {
		return glfwGetTime();
	}

	double Timer::GetTimeMS() {
		return glfwGetTime() / 1000;
	}

	double Timer::GetTimeUS() {
		return glfwGetTime() / 1000000;
	}

}