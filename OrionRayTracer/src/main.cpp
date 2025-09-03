#include <Vega.h>
#include <memory>
#include "DebugWindow.h"
#include "ObjectManager.h"
#include<stdlib.h>
#include <numbers>
#include "ScreenDisplay.h"
#include "RayTracing.h"

class RunLayer : public Vega::Layer {
	void OnAttach() override {
		_app = Vega::Application::Get();
	}

	void OnUpdate() override {
	}

private:
	Vega::Application* _app = nullptr;
};

class Orion : public Vega::Application {
public:
	Orion() {
		Log::trace("Opened Orion Ray Tracer");

		AttachLayer(new ComputeLayer());
		AttachLayer(new ScreenDisplay());

		auto imgui = new Vega::ImGuiLayer(GetWindow());
		imgui->AttachCanvas(new DebugWindow());
		AttachLayer(imgui);
	}

	~Orion() override {
		Log::info("Closed Orion Ray Tracer");
	}
};

std::unique_ptr<Vega::Application> Vega::CreateApplication() {
	return std::make_unique<Orion>();
}