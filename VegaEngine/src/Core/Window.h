#pragma once
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM 
#include "Log.h"
#include "OpenGL.h"

namespace Vega {

	struct WindowData {
		GLuint width;
		GLuint height;
		const char* name;
		bool vsync;
	};

	class Window {
	public:
		Window();
		~Window();

		GLFWwindow* GetGLFWWindow();

		GLFWwindow* Create(const WindowData& props);
		void OnUpdate();
		void Shutdown();

		void Resize(GLuint width, GLuint height);

		void CenterCursor(bool enable);

		GLuint GetWidth() const;
		GLuint GetHeight() const;
		bool IsVsync() const;
		void SetVsync(bool enable);


	private:

		static inline bool _GLFWinitialized = false;

		GLFWwindow* _window = nullptr;
		WindowData _data{};
		bool _GLADinitialized = false;
	};
}