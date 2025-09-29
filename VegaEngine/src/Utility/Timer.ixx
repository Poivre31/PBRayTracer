export module Utility:Timer;
import std;

//void PrintTime() {
//	auto time = zoned_time{ current_zone(), system_clock::now() };
//	std::println("Time is: {}", time);
//}

using namespace std::chrono;

namespace Vega {

	export class Timer {
	public:

		Timer() {
			_watchTime = TimeS();
		}

		void ResetWatch() {
			_watchTime = TimeS();
		}

		double WatchTimeS() const {
			return TimeS() - _watchTime;
		}

		static void Init() {
			_startTime = 0;
			_currTime = 0;
			_frameCount = 0;
		}

		static double TimeS() {
			return double((steady_clock::now().time_since_epoch() - _epoch).count()) / 1000000000;
		}

		static double TimeMS() {
			return double((steady_clock::now().time_since_epoch() - _epoch).count()) / 1000000;
		}

		static double TimeUS() {
			return double((steady_clock::now().time_since_epoch() - _epoch).count()) / 1000;
		}

		static double TimeSinceStartup() {
			return TimeS() - _startTime;
		}

        static auto ZoneTime() {
			return zoned_time<seconds>{ current_zone(), time_point_cast<seconds>(system_clock::now()) };
        }

		static void OnUpdate() {
			_prevTime = _currTime;
			_currTime = TimeS();
			_frameCount++;
		}

		static double DeltaTime() {
			return _currTime - _prevTime;
		}

		static size_t FrameCount() {
			return _frameCount;
		}

	private:
		double _watchTime = 0.;

		static inline double _startTime = 0.;
		static inline double _prevTime = 0.;
		static inline double _currTime = 0.;
		static inline size_t _frameCount = 0;
		static inline auto _epoch = steady_clock::now().time_since_epoch();
	};

}