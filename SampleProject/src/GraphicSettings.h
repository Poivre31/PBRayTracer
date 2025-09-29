#pragma once

import Vega;

struct GraphicSettings {

	float luminosity = 1.f;
	float gamma = 2.2f;
	float saturation = 1.f;

};

class GraphicSettingsWindow : public Vega::GuiCanvas {
public:
	GraphicSettingsWindow(GraphicSettings* settings) : _settings(settings) {};

	void Draw() {
		Vega::Slider("Luminosity", _settings->luminosity, 0.f, 10.f);
		Vega::Slider("Gamma", _settings->gamma, .25f, 4.f);
		Vega::Slider("Saturation", _settings->saturation, .0f, 2.f);
	}

private:
	GraphicSettings* _settings;
};

class GraphicSystem : public Vega::Layer {
public:
	static GraphicSystem* Get() {
		if (!_instance)
			_instance = new GraphicSystem();
		return _instance;
	}

	GraphicSettings* Settings() {
		return &_settings;
	}

	void OnAttach() override {
		Vega::Systems::Gui()->AttachCanvas<GraphicSettingsWindow>("Graphic settings", Get()->Settings());
	}

private:
	static inline GraphicSystem* _instance = nullptr;
	GraphicSettings _settings{};
};