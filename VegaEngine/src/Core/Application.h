#pragma once
#include "Window.h"
#include "LayerStack.h"
#include <memory>
#include "Timer.h"
#include <variant>
#include "Scene/Scene.h"

namespace Vega {

	class Application
	{
	public:

		Application();
		virtual ~Application();

		void Init();
		void Run();
		void Shutdown();
		void PlanShutdown();

		static Application* Get();
		Window* GetWindow();
		Scene* GetScene() {
			return _scene.get();
		}


		virtual void Resize(GLuint width, GLuint height);

		void AttachLayer(Layer* layer);
		void DetachLayers(Layer* layer);
		void ClearLayers();

	private:
		static inline Application* _instance = nullptr;
		static inline bool _initialised = false;
		
		bool _running = false;
		bool _shouldClose = false;
		LayerStack _layerStack;
		Window* _window = nullptr;
		GLFWwindow* _glfwWindow = nullptr;
		std::unique_ptr<Scene> _scene;
	};

	std::unique_ptr<Vega::Application> CreateApplication();
}

