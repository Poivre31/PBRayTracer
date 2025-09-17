module;
#include "OpenGL.h"
export module EntryPoint;

import std;
import Core;

extern std::unique_ptr<Vega::Application> Vega::CreateApplication();

int main() {
	auto app = Vega::CreateApplication();
	app->Run();
}