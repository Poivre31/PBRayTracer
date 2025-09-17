#pragma once
#include "OrionLogger.h"
#include "imgui.h"

import Vega;

class DebugWindow : public Vega::GuiCanvas {
public:
	void Draw() final {
		ImGui::Begin("Debug window");
		if (ImGui::Button("Click")) OrionLog.info("Clicked button");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};
