#pragma once
#include "DebugWindow.h"
#include "Wave/Wave.h"
#include "GraphicSettings.h"
#include "Gravity/Gravity.h"

import Vega;

class AppLayer : public Vega::Layer {
public:
	void OnAttach() override {
#ifndef DEBUG
#endif
		Log.EnableLogLevel(Vega::LogLevel::Debug, false);

		Log.debug("Welcome to my project! ");
		auto* _app = Vega::Systems::Application();

		_app->AttachLayer<DebugLayer>("My constructor message");
		_app->AttachLayer<GravityDisplay>();
		_app->AttachLayer<GraphicSystem>();
	}
};