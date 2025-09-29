module;
#include <glad/gl.h>
#include <GLFW/glfw3.h>

export module Core:Window;
import Utility;


namespace Vega {

	export void CloseEvent(GLFWwindow* window);
	export void ResizeEvent(GLFWwindow* window, int width, int height);

	export struct WindowData {
		const char* name = "Application";
		GLuint width = 1280;
		GLuint height = 720;
		bool vsync = true;
	};

	export class Window final {

	public:
		Window();
		~Window();

		GLFWwindow* GetGLFWWindow();

		GLFWwindow* Create(const WindowData& props);
		void OnUpdate();
		void Shutdown();

		void Resize(GLuint width, GLuint height);

		void CenterCursor(bool enable);

		GLuint Width() const;
		GLuint Height() const;
		bool IsVsync() const;
		void SetVsync(bool enable);


	private:
		static inline bool _GLFWinitialized = false;

		GLFWwindow* _window = nullptr;
		WindowData _data{};
		bool _GLADinitialized = false;
	};
}