#pragma once
#include <Vega.h>

class DebugWindow : public Vega::ImGuiInterface {
public:
	void Draw() final {
		ImGui::Begin("Debug window");
		if (ImGui::Button("Click")) spdlog::info("Clicked button");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};