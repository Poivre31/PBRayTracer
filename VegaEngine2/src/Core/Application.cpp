module;
#include <glad/gl.h>
#include <GLFW/glfw3.h>
module Core;

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
		Application* app = Application::Get();
		Window* _window = app->GetWindow();

		if (!_window) {
			Log.error("Resizing window before window creation");
		}
		_window->Resize(width, height);

		app->Resize((GLuint)width, (GLuint)height);
	}
}

namespace Vega {
	const static int defaultWidth = 1920;
	const static int defaultHeight = 1080;

	Application::Application() {
		_instance = this;
		Init();
	}

	Application::~Application() = default;

	void Application::Init() {
		if (_initialised) {
			Log.error("Application already initialised, shutdown before new call to Init");
			return;
		}
		Log.trace("### LAUNCHING ###\n", Color::Yellow);
		_instance = this;
		_window = std::make_unique<Window>();
		_window->Create({ defaultWidth, defaultHeight, "Orion Ray Tracer", true });

		_running = true;
		_initialised = true;

		//_scene = std::make_unique<Scene>();
		//_IO = new IOLayer(_window.get());
		//_layerStack.AttachLayer(_IO);
		Timer::Init();

		Log.trace("Launched Vega engine");
	}

	void Application::Run() {
		if (!_initialised) {
			Log.error("Running application before initialisation");
			return;
		}
		std::cout << "\n";
		Log.trace("### RUNNING ###\n", Color::Yellow);
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
			//if (_scene)
			//	_scene->OnUpdate();
			Timer::OnUpdate();


			//TO FIX: UNUSUALLY LONG FRAME TIME AT STARTUP CAUSING LARGE ERRORS
			double deltaTime = Timer::GetDeltaTime();
			deltaTime = std::min(deltaTime, 1. / 60);
			for (Layer* layer : _layerStack)
			{
				layer->OnPhysicsUpdate(deltaTime);
			}
			//if (_scene)
			//	_scene->OnPhysicsUpdate(deltaTime);


			_window->OnUpdate();

		}
	}

	void Application::Shutdown() {
		if (!_initialised) {
			Log.error("Shuting down application before initialisation");
			return;
		}

		std::cout << "\n";
		Log.trace("### SHUTTING DOWN ###\n", Color::Yellow);

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

	//Scene* Application::GetScene() {
	//	return _scene.get();
	//}
	//IOData Application::GetIOData() {
	//	return _IO->GetData();
	//}

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