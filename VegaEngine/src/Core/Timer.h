#pragma once
#include "OpenGL.h"
#include "Layer.h"
#include <chrono>
using namespace std::chrono;

namespace Vega {

	class Timer {
	public:

		static void Init() {
			_epoch = steady_clock::now().time_since_epoch();
			_startTime = 0;
			_currTime = 0;
			_frameCount = 0;
		}

		static double GetTimeMS();

		static double GetTimeUS();

		static double GetTimeS();

		static double GetTimeSinceStartup();

		static void OnUpdate() {
			_prevTime = _currTime;
			_currTime = GetTimeS();
			_frameCount++;
		}

		static double GetDeltaTime() {
			return _currTime - _prevTime;
		}

		static size_t GetFrameCount() {
			return _frameCount;
		}

		static void PrintTime() {
			auto time = zoned_time{ current_zone() };
			std::println("Time is: {}", time);
		}

	private:
		static inline double _startTime = 0.;
		static inline double _prevTime = 0.;
		static inline double _currTime = 0.;
		static inline size_t _frameCount = 0;
		static inline auto _epoch = steady_clock::now().time_since_epoch();
	};

}