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
			_watchTime = GetTimeS();
		}

		void ResetWatch() {
			_watchTime = GetTimeS();
		}

		double GetWatchTimeS() const {
			return GetTimeS() - _watchTime;
		}

		static void Init() {
			_startTime = 0;
			_currTime = 0;
			_frameCount = 0;
		}

		static double GetTimeS() {
			return double((steady_clock::now().time_since_epoch() - _epoch).count()) / 1000000000;
		}

		static double GetTimeMS() {
			return double((steady_clock::now().time_since_epoch() - _epoch).count()) / 1000000;
		}

		static double GetTimeUS() {
			return double((steady_clock::now().time_since_epoch() - _epoch).count()) / 1000;
		}

		static double GetTimeSinceStartup() {
			return GetTimeS() - _startTime;
		}

        static auto GetZoneTime() {
			return zoned_time<seconds>{ current_zone(), time_point_cast<seconds>(system_clock::now()) };
        }

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

	private:
		double _watchTime = 0.;

		static inline double _startTime = 0.;
		static inline double _prevTime = 0.;
		static inline double _currTime = 0.;
		static inline size_t _frameCount = 0;
		static inline auto _epoch = steady_clock::now().time_since_epoch();
	};

}