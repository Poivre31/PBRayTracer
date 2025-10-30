#pragma once
#include "DebugWindow.h"
#include "Wave/Wave2.h"
#include "GraphicSettings.h"

import Vega;

class AppLayer : public Vega::Layer {
public:
	void OnAttach() override {
#ifndef DEBUG
#endif
		Log.EnableLogLevel(Vega::LogLevel::Debug, false);

		Log.debug("Welcome to my project! ");
		auto* _app = Vega::Systems::Application();

		_app->AttachLayer<DebugLayer>("Hey");
		_app->AttachLayer<WaveDisplay>();
	}
};