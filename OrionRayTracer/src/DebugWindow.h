#pragma once
#include "OrionLogger.h"

import Vega;

class DebugWindow : public Vega::GuiCanvas {
public:
	void Draw() final {
		if (Vega::Button("Click me")) OrionLog.info("Clicked button");
	}
};
