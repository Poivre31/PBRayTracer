#pragma once
#include "Core/Application.h"

extern std::unique_ptr <Vega::Application> Vega::CreateApplication();

#ifdef DIST

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	auto app = Vega::CreateApplication();
	app->Run();
}

#else

int main() {
	auto app = Vega::CreateApplication();
	app->Run();
}

#endif // 

