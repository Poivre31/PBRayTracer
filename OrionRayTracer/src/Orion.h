#pragma once
#include "DebugWindow.h"
#include "ComputeLayer.h"
#include "Boids.h"

import Vega;

static const auto screenVert = "res/fullScreenQuad.vert";
static const auto screenFrag = "res/fullScreenQuad.frag";

class AppLayer : public Vega::Layer {
public:
	AppLayer(Vega::Application* app) : _app(app) {};

	void OnAttach() override {
		_app->GetGUI()->AttachCanvas<DebugWindow>();

		_app->AttachLayer<BoidsLayer>();
		//_app->AttachLayer<ComputeLayer>();

		_app->AttachLayer<Vega::ScreenQuad>(new Vega::Shader(screenVert, screenFrag));

		OrionLog.trace("Application launched");
	}

	void OnDetach() override {
		OrionLog.trace("Application closed");
	}

private:
	Vega::Application* _app = nullptr;
};