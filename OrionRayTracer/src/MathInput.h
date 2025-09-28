#pragma once
#include "imgui.h"

import Vega;
import std;

struct MathData {

	std::array<float, 2> range{1.,1.};
	float a = 0.f;
	float wl = 1.f;
	float gamma = 1.f;
	float intensity = 1.f;
	float L = 0.001f;
	int n = 0;
};

class InputCanvas : public Vega::GuiCanvas {
public:
	
	void Draw() override {
		ImGui::SliderFloat("Input range (x)", _data.range.data(), 0.1f,100.f);
		float aspectRatio = float(Vega::Application::Get()->GetWindow()->GetHeight()) / Vega::Application::Get()->GetWindow()->GetWidth();
		_data.range[1] = _data.range[0] * aspectRatio;
		ImGui::SliderFloat("Seperation", &_data.a, 0.f, 10.f);
		ImGui::SliderFloat("Wavelength", &_data.wl, 0.1f, 10.f);		
		ImGui::SliderFloat("Gamma", &_data.gamma, 1.f, 3.f);
		ImGui::SliderFloat("Intensity", &_data.intensity, 0.1f, 10.f);
		ImGui::SliderFloat("Distance L", &_data.L, 0.001f, 10.f);
		ImGui::SliderInt("Number of sources", &_data.n, 0, 256);

	}

	MathData* GetData() {
		return &_data;
	}

private:
	MathData _data;

};