#include "App.h"
#include <Windows.h>
import Vega;
import std;

// Set the initial settings of the application here
auto appSpec = Vega::ApplicationSpec{
	.windowData = {
		.name = "My Project",
		.width = 1080,
		.height = 1080,
		.vsync = true,
	}
};

// This code is for building as a Window App (distribution build by default)
#ifdef WINDOWS
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	auto app = std::make_unique<Vega::Application>(appSpec);

	app->AttachLayer<AppLayer>();
	app->Run();
}

#elifdef CONSOLE
// And this is for a console app (debug and realese by default)
int main() {
	auto app = std::make_unique<Vega::Application>(appSpec);

	app->AttachLayer<AppLayer>();
	app->Run();
}
#endif