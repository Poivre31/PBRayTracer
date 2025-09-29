#pragma once
#include "imgui.h"

import Vega;
import std;

using namespace Vega::Math;

struct MathData {
	float2 range{ 1.,1. };
	float a = 0.f;
	float wl = 1.f;
	float gamma = 1.f;
	float intensity = 1.f;
	float L = 0.001f;
	int n = 1;
	//Vega::DataContainer<float2> range = { "Range", {1.f, 1.f }, 0.1f, 10.f };
	//Vega::DataContainer<float> separation = { "Separation", 0.f, 0.f, 10.f };
	//Vega::DataContainer<float> wavelength = { "Wavelength", 1.f, 0.1f, 2.f };
	//Vega::DataContainer<float> gamma = { "Gamma", 1.f, 1.f, 3.f };
	//Vega::DataContainer<float> intensity = { "Intensity", 1.f, 0.1f, 10.f };
	//Vega::DataContainer<float> distance = { "Distance", 0.f, 0.f, 100.f };
	//Vega::DataContainer<int> numberSources = { "Number", 1, 0, 256 };
};

class InputCanvas : public Vega::GuiCanvas {
public:

	InputCanvas(MathData* data) : _data(data) {};

	void SetData(MathData* data) {
		_data = data;
	}

	void Draw() override {
		Vega::Slider("Input range (x)", _data->range[0], 0.1f, 100.f);
		float aspectRatio = float(Vega::Systems::Window()->Height()) / Vega::Systems::Window()->Width();
		_data->range[1] = _data->range[0] * aspectRatio;
		Vega::Slider("Seperation", _data->a, 0.f, 10.f);
		Vega::Slider("Wavelength", _data->wl, 0.1f, 10.f);
		Vega::Slider("Gamma", _data->gamma, 1.f, 3.f);
		Vega::Slider("Intensity", _data->intensity, 0.1f, 10.f);
		Vega::Slider("Distance L", _data->L, 0.001f, 10.f);
		Vega::Slider("Number of sources", _data->n, 0, 256);
	}

private:
	MathData* _data;
};