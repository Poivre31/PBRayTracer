#include "Application.h"
#include "Window.h"
#include "Log.h"
#include <iostream>
#include "imgui.h"

namespace Vega {
	const static int defaultWidth = 1920;
	const static int defaultHeight = 1080;

	void OnLayerDestruction(Layer* layer) {
#ifdef DEBUG
		//Vega::debug(std::format("Destroyed layer: '{}'", layer->GetName()));
#endif
		Application::Get()->DetachLayers(layer);
	}

	void CloseEvent(GLFWwindow* window) {
		Application::Get()->Shutdown();
	}
	
	void ResizeEvent(GLFWwindow* window, int width, int height) {
		Application* app = Application::Get();
		Window* _window = app->GetWindow();

		if (!_window) {
			Log::error("Resizing window before window creation");
		}
		_window->Resize(width, height);

		app->Resize((GLuint)width, (GLuint)height);
	}

	Application::Application() {
		SetLogLevel();
		_instance = this;
		Init();
	}

	Application::~Application() = default;

	void Application::Init() {
		if (_initialised) {
			Log::error("Application already initialised, shutdown before new call to Init");
			return;
		}
		Log::trace("### LAUNCHING ###\n", Log::Color::Yellow);
		_instance = this;
		_window = new Window();
		GLFWwindow* glfwWindow = _window->Create({ defaultWidth, defaultHeight, "Orion Ray Tracer", false });

		_running = true;
		_initialised = true;

		Timer::Init();

		Log::info("Launched Vega engine");
	}

	void Application::Run() {
		if (!Application::_instance) {
			Log::error("Running application before initialisation");
			return;
		}
		std::cout << "\n";
		Log::trace("### RUNNING ###\n", Log::Color::Yellow);
		while (_running) {
			if (_shouldClose) {
				Shutdown();
				return;
			}

			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : _layerStack)
			{
				layer->OnUpdate();
			}

			Timer::OnUpdate();


			//TO FIX: UNUSUALLY LONG FRAME TIME AT STARTUP CAUSING LARGE ERRORS
			double deltaTime = Timer::GetDeltaTime();
			deltaTime = std::min(deltaTime, 1. / 60);
			for (Layer* layer : _layerStack)
			{
				layer->OnPhysicsUpdate(deltaTime);
			}


			_window->OnUpdate();

		}
	}

	void Application::Shutdown() {
		if (!_initialised) {
			Log::error("Shuting down application before initialisation");
			return;
		}

		std::cout << "\n";
		Log::trace("### SHUTTING DOWN ###\n", Log::Color::Yellow);

		_running = false;

		if (_window) {
			_window->Shutdown();
			delete _window;
			_window = nullptr;
		}

		_layerStack.ClearLayers();

		_initialised = false;
		Log::info("Shut down Vega engine");
	}

	void Application::PlanShutdown() {
		_shouldClose = true;
	}

	Application* Application::Get() {
		if (!_instance) {
			Log::error("No application created");
		}
		return _instance;
	}

	Window* Application::GetWindow() {
		if (!_window) {
			Log::error("Getting window before window creation");
		}
		return _window;
	}

	void Application::AttachLayer(Layer* layer) {
		_layerStack.AttachLayer(layer);
	}

	void Application::DetachLayers(Layer* layer) {
		_layerStack.DetachLayers(layer);
	}
	void Application::ClearLayers() {
		_layerStack.ClearLayers();
	}

	void Application::Resize(GLuint width, GLuint height) {}

}