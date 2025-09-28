#include "Orion.h"
#include <Windows.h>
import Vega;

#ifdef DIST
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	auto appSpec = Vega::ApplicationSpec();
	appSpec.windowData.name = "Optics";
	appSpec.windowData.height = 1080;
	appSpec.windowData.width = 1080;
	appSpec.windowData.vsync = true;

	auto app = std::make_unique<Vega::Application>(appSpec);

	app->AttachLayer<AppLayer>(app.get());
	app->Run();
}



#else
int main() {
	auto appSpec = Vega::ApplicationSpec();
	appSpec.windowData.name = "Optics";
	appSpec.windowData.height = 1080;
	appSpec.windowData.width = 1080;
	appSpec.windowData.vsync = true;

	auto app = std::make_unique<Vega::Application>(appSpec);

	app->AttachLayer<AppLayer>(app.get());
	app->Run();
}
#endif