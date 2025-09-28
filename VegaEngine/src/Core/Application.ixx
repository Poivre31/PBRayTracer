module;
#include "OpenGL.h"

export module Core:Application;
import :Scene;
import :LayerStack;
import :Layer;
import :Window;
import :ImGuiLayer;
import :IOLayer;
import Utility;
import std;

namespace Vega {

	export struct ApplicationSpec {
		WindowData windowData{};
	};

	export class Application
	{
	public:

		Application(ApplicationSpec spec);
		virtual ~Application();

		void Init(ApplicationSpec spec);
		void Run();
		void Shutdown();
		void PlanShutdown();

		static Application* Get();
		Window* GetWindow();
		ImGuiLayer* GetGUI();
		Scene* GetScene();
		IOData GetIOData();

		void Resize(GLuint width, GLuint height);

		template <std::derived_from<Layer> T, typename ...Args>
		T* AttachLayer(Args... args) {
			T* layer = new T(args...);
			_layerStack.AttachLayer(layer);
			return layer;
		}
		void AttachLayer(Layer* _layer) {
			_layerStack.AttachLayer(_layer);
		}
		void DetachLayers(Layer* layer);
		void ClearLayers();

	private:
		static inline Application* _instance = nullptr;
		static inline bool _initialised = false;

		bool _running = false;
		bool _shouldClose = false;
		LayerStack _layerStack;

		ImGuiLayer* _guiLayer;
		IOLayer* _IO;
		Scene* _scene;
		std::unique_ptr<Window> _window;
	};

	export std::unique_ptr<Application> CreateApplication();

	export void CloseEvent(GLFWwindow* window);
	export void ResizeEvent(GLFWwindow* window, int width, int height);
}
