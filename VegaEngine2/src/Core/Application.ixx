module;
#include <glad/gl.h>
#include <GLFW/glfw3.h>

export module Core:Application;
import :LayerStack;
import :Layer;
import :Timer;
import :Log;
import :Window;
import std;

namespace Vega {

	export class Application
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
		//Scene* GetScene();
		//IOData GetIOData();

		void Resize(GLuint width, GLuint height);

		void AttachLayer(Layer* layer);
		void DetachLayers(Layer* layer);
		void ClearLayers();

	private:
		static inline Application* _instance = nullptr;
		static inline bool _initialised = false;

		bool _running = false;
		bool _shouldClose = false;
		LayerStack _layerStack;
		//IOLayer* _IO;
		std::unique_ptr<Window> _window;
		//std::unique_ptr<Scene> _scene;
	};

	export std::unique_ptr<Application> CreateApplication();

	export void CloseEvent(GLFWwindow* window);
	export void ResizeEvent(GLFWwindow* window, int width, int height);
}
