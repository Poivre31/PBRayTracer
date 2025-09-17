#include "imgui.h"
#include "DebugWindow.h"
#include "ScreenDisplay.h"
#include "ComputeLayer.h"
import Vega;

class Orion : public Vega::Application {
public:
	Orion() {
		OrionLog.trace("Opened Orion Ray Tracer");
		GetGUI()->AttachCanvas<DebugWindow>()->AttachCanvas<DebugWindow>();
		AttachLayer<ComputeLayer>();
		AttachLayer<ScreenDisplay>();
	}

	~Orion() override {
		OrionLog.trace("Closed Orion Ray Tracer");
	}
};

std::unique_ptr<Vega::Application> Vega::CreateApplication() {
	return std::make_unique<Orion>();
}

int main() {
	auto app = Vega::CreateApplication();
	app->Run();
}