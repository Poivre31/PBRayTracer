#pragma once
#include "LampI.h"

struct LampSettings {

	int nLamps = 1;
	float wavelength = .1;
	int renderMode = RenderColorPosition;

};

class LampWindow : public Vega::GuiCanvas {
public:
	LampWindow(LampSettings* settings) : _settings(settings) {}

	void Draw() override {
		Vega::Combo("Rendering mode", { "Pos", "PosXVel", "Cheh" }, _settings->renderMode);
		int maxLamps = 10;
		if (_settings->renderMode == RenderColorCrossSpeed)
			maxLamps = 1000;
		static int nBase = _settings->nLamps;
		static int nMul = 1;
		Vega::Slider("Number of lamps", nBase, 0, 10);
		Vega::Slider("Multiplier", nMul, 1, 1000);
		_settings->nLamps = nBase * nMul;
		Vega::Slider("Wavelength", _settings->wavelength, .01f, 1.f);
		int a = 0;
	}

private:
	LampSettings* _settings;
};