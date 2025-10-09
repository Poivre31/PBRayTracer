module;
#include "OpenGL.h"
module Core;
import :Application;
import Utility;

namespace Vega {
	//static void OnLayerDestruction(Layer* layer) {
	//	//#ifdef DEBUG
	//	//		Log.debug(std::format("Destroyed layer: '{}'", layer->GetName()));
	//	//#endif
	//	Application::Get()->DetachLayers(layer);
	//}

	void CloseEvent(GLFWwindow* window) {
		Application::Get()->Shutdown();
	}

	void ResizeEvent(GLFWwindow* window, int width, int height) {
		auto* app = Application::Get();
		auto* _window = app->GetWindow();

		if (!_window) {
			Log.error("Resizing window before window creation");
		}
		_window->Resize(width, height);

		app->Resize((GLuint)width, (GLuint)height);
	}
}

namespace Vega {

	Application::Application(ApplicationSpec spec) {
		_instance = this;
		Init(spec);
	};

	Application::~Application() = default;

	void Application::Init(ApplicationSpec spec) {
		if (_initialised) {
			Log.error("Application already initialised, shutdown before new call to Init");
			return;
		}
		Log.trace<Color::Yellow>("### LAUNCHING ###\n");
		_instance = this;
		_window = std::make_unique<Window>();
		_window->Create(spec.windowData);

		_guiLayer = AttachLayer<ImGuiLayer>(_window.get());
		_drawingLayer = AttachLayer<DrawingLayer>(_window.get());
		AttachLayer<Vega::ScreenQuad>(_drawingLayer->GetShader());
		_IO = AttachLayer<IOLayer>(_window.get());
		_scene = AttachLayer<Scene>();

		_running = true;
		_initialised = true;

		Timer::Init();

		Log.trace("Launched Vega engine");
	}

	void Application::Run() {
		if (!_initialised) {
			Log.error("Running application before initialisation");
			return;
		}

		std::println();
		Log.trace<Color::Yellow>("### RUNNING ###\n");
		while (_running) {
			if (_shouldClose) {
				Shutdown();
				return;
			}

			glClear(GL_COLOR_BUFFER_BIT);

			Timer::OnUpdate();
			//TO FIX: UNUSUALLY LONG FRAME TIME AT STARTUP CAUSING LARGE ERRORS
			double deltaTime = std::min(Timer::DeltaTime(), 1. / 60);
			for (Layer* layer : _layerStack)
			{
				layer->OnUpdate(deltaTime);
			}

			_window->OnUpdate();

		}
	}

	void Application::Shutdown() {
		if (!_initialised) {
			Log.error("Shuting down application before initialisation");
			return;
		}

		std::println();
		Log.trace<Color::Yellow>("### SHUTTING DOWN ###\n");

		_running = false;

		if (_window) {
			_window->Shutdown();
			_window.reset();
			_window = nullptr;
		}

		_layerStack.ClearLayers();

		_initialised = false;
		Log.trace("Shut down Vega engine");
	}

	void Application::PlanShutdown() {
		_shouldClose = true;
	}

	Application* Application::Get() {
		if (!_instance) {
			Log.error("No application created");
		}
		return _instance;
	}

	Window* Application::GetWindow() {
		if (!_window) {
			Log.error("Getting window before window creation");
		}
		return _window.get();
	}

	DrawingLayer* Application::GetDrawStack() {
		return _drawingLayer;
	}


	ImGuiLayer* Application::GetGUI() {
		return _guiLayer;
	}
	
	Scene* Application::GetScene() {
		return _scene;
	}
	IOData Application::GetIOData() {
		return _IO->GetData();
	}

	void Application::DetachLayers(Layer* layer) {
		_layerStack.DetachLayers(layer);
	}
	void Application::ClearLayers() {
		_layerStack.ClearLayers();
	}

	void Application::Resize(GLuint width, GLuint height) {
		for (Layer* layer : _layerStack)
		{
			layer->OnResize(width, height);
		}
	}

}