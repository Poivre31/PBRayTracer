#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "Orion.h"

import std;
import Vega;

class MyLayer : public Vega::Layer {
public:
	void OnResize(GLuint width, GLuint height) override {
		Vega::Log.debug(std::format("Width: {}, height: {}", (int)width, (int)height));
	}

};

int main() {
	//Vega::Log.trace("Hello from Vega engine");
	//Vega::Log.info(std::format("{}",Vega::Timer::GetTimeUS()));
	//auto layer = MyLayer();
	//layer.OnResize((int)1920, (int)1080);
	auto app = Vega::CreateApplication();
	app->Run();
}