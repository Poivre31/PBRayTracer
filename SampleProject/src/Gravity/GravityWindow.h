#pragma once

import Vega;

struct GravitySettings {

	int nParticles = 1;
	int nDisplay = 1;
	float gravityConstant = 1.;
	float zPos = 0.f;

};

class GravityWindow : public Vega::GuiCanvas {
public:
	GravityWindow(GravitySettings* settings) : _settings(settings) {}

	void Draw() override {
		Vega::Slider("Number of particles", _settings->nParticles, 0, 100000);
		_settings->nDisplay = std::min(_settings->nDisplay, _settings->nParticles/10);
		Vega::Slider("Displayed particles", _settings->nDisplay, 0, _settings->nParticles/10);
		Vega::Slider("Gravity constant", _settings->gravityConstant, .001f, 10.f);
		Vega::Slider("Z slice", _settings->zPos, 0.f, 1.f);
	}

private:
	GravitySettings* _settings;
};