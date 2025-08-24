#include "Application.h"
#include "Window.h"
#include "Log.h"
#include <iostream>

namespace Vega {

	static void CloseEvent(GLFWwindow* window) {
		Window::Get()->Close();
		glfwTerminate();
		Application::Get()->Close();
	}
	
	static void ResizeEvent(GLFWwindow* window, int width, int height) {
		Window::Get()->Resize(width, height);
		Application::Get()->Resize((UINT)width, (UINT)height);
	}

	Application::Application() {
		SetLogLevel();
		spdlog::info("Launched Vega engine");
		_window = std::make_unique<Window>();
		GLFWwindow* glfwWindow = _window->Create({ 1280, 720, "Orion Ray Tracer", false });
		glfwSetWindowCloseCallback(glfwWindow, CloseEvent);
		glfwSetWindowSizeCallback(glfwWindow, ResizeEvent);
		_instance = this;
		_running = true;
		glClearColor(1, 0, 1, 1);
	}

	Application::~Application() = default;

	void Application::Run() {
		while (_running) {
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : _layerStack)
			{
				layer->OnUpdate();
			}

			_window->OnUpdate();
		}
	}

	Application* Application::Get() {
		if (!_instance) {
			spdlog::warn("No application created");
		}
		return _instance;
	}

	Window* Application::GetWindow() {
		return _window.get();
	}

	void Application::AttachLayer(Layer* layer) {
		_layerStack.AttachLayer(layer);
	}
	void Application::DetachLayer(Layer* layer) {
		_layerStack.DetachLayer(layer);
	}
	void Application::ClearLayers() {
		_layerStack.ClearLayers();
	}

	void Application::Close() {
		_running = false;
	}

	void Application::Resize(UINT width, UINT height) {}

} // namespace Vega