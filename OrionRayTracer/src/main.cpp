#include "Orion.h"
import Vega;

int main() {
	auto appSpec = Vega::ApplicationSpec();
	appSpec.windowData.name = "Orion ray tracer";
	appSpec.windowData.vsync = false;

	auto app = std::make_unique<Vega::Application>(appSpec);

	app->AttachLayer<AppLayer>(app.get());
	app->Run();
}