#pragma once
#include <Vega.h>

class DebugWindow : public Vega::ImGuiCanvas {
public:
	void Draw() final {
		ImGui::Begin("Debug window");
		if (ImGui::Button("Click")) Log::info("Clicked button");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};