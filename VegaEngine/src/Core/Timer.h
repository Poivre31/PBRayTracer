#pragma once
#include "OpenGL.h"
#include "Layer.h"

namespace Vega {

	class Timer {
	public:

		static double GetTimeMS();

		static double GetTimeUS();

		static double GetTimeS();

	};

}