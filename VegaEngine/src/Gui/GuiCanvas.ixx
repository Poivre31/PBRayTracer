module;
#include "imgui.h"
export module Gui:Canvas;
import std;
import Math;

export namespace Vega {

	bool Slider(std::string name, float& data, float min, float max) {
		return ImGui::SliderFloat(name.data(), &data, min, max);
	}
	bool Slider(std::string name, Math::float2& data, float min, float max) {
		return ImGui::SliderFloat2(name.data(), data.data(), min, max);
	}
	bool Slider(std::string name, Math::float3& data, float min, float max) {
		return ImGui::SliderFloat3(name.data(), data.data(), min, max);
	}
	bool Slider(std::string name, Math::float4& data, float min, float max) {
		return ImGui::SliderFloat4(name.data(), data.data(), min, max);
	}

	bool Slider(std::string name, int& data, int min, int max) {
		return ImGui::SliderInt(name.data(), &data, min, max);
	}
	bool Slider(std::string name, Math::int2& data, int min, int max) {
		return ImGui::SliderInt2(name.data(), data.data(), min, max);
	}
	bool Slider(std::string name, Math::int3& data, int min, int max) {
		return ImGui::SliderInt3(name.data(), data.data(), min, max);
	}
	bool Slider(std::string name, Math::int4& data, int min, int max) {
		return ImGui::SliderInt4(name.data(), data.data(), min, max);
	}

	void Text(std::string text) {
		ImGui::Text(text.data());
	}

	bool Button(std::string name) {
		return ImGui::Button(name.data());
	}

	bool Combo(const char* name, std::vector<const char*> options, int& result) {
		static const char* item = options[0];
		bool clicked = false;
		if (ImGui::BeginCombo(name, item))
		{
			int i = 0;
			for (auto& o : options)
			{
				bool is_selected = (item == o);
				if (ImGui::Selectable(o, is_selected)) {
					clicked = true;
					result = i;
					item = o;
				}
				if (is_selected) {
					ImGui::SetItemDefaultFocus();
				}
				i++;
			}
			ImGui::EndCombo();
		}
		return false;
	}

	void ImGuiDemo() {
		ImGui::ShowDemoWindow();
	}

	class GuiCanvas
	{
	public:
		GuiCanvas() = default;
		virtual ~GuiCanvas() = default;

		//template <std::derived_from<GuiElement> T, typename ...Args>
		//void AddElement(Args... args) {
		//	_elements.push_back(new T(args...));
		//}

		virtual void Draw() = 0;

	};

}

