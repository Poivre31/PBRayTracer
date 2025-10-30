module;
#include "imgui.h"
export module Gui:Canvas;
import std;
import Math;

export namespace Vega {

	bool Slider(const char* name, float& data, float min, float max) {
		return ImGui::SliderFloat(name, &data, min, max);
	}
	bool Slider(const char* name, float2& data, float min, float max) {
		return ImGui::SliderFloat2(name, data.data(), min, max);
	}
	bool Slider(const char* name, float3& data, float min, float max) {
		return ImGui::SliderFloat3(name, data.data(), min, max);
	}
	bool Slider(const char* name, float4& data, float min, float max) {
		return ImGui::SliderFloat4(name, data.data(), min, max);
	}

	bool Slider(const char* name, int& data, int min, int max) {
		return ImGui::SliderInt(name, &data, min, max);
	}
	bool Slider(const char* name, int2& data, int min, int max) {
		return ImGui::SliderInt2(name, data.data(), min, max);
	}
	bool Slider(const char* name, int3& data, int min, int max) {
		return ImGui::SliderInt3(name, data.data(), min, max);
	}
	bool Slider(const char* name, int4& data, int min, int max) {
		return ImGui::SliderInt4(name, data.data(), min, max);
	}

	void Text(std::string text) {
		ImGui::Text(text.data());
	}
	void Text(const char* text) {
		ImGui::Text(text);
	}

	bool Button(const char* name) {
		return ImGui::Button(name);
	}

	bool ColorPicker(const char* name, Vec3<float> &color) {
		return ImGui::ColorEdit3(name, &color.x);
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

	void Separator() {
		ImGui::Separator();
	}

	void Separator(const char* title) {
		ImGui::SeparatorText(title);
	}

	void ImGuiDemo() {
#ifdef DIST
		return;
#endif // DIST

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

