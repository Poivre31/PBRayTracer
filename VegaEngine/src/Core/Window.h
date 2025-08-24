#pragma once
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM 
#include "Log.h"
#include "OpenGL.h"

struct GLFWwindow;

namespace Vega {

	struct WindowData {
		UINT width;
		UINT height;
		const char* name;
		bool vsync;
	};

	class Window {
	public:
		Window();
		virtual ~Window();

		static Window* Get();
		GLFWwindow* GetGLFWWindow();

		GLFWwindow* Create(const WindowData& props);
		void OnUpdate();
		void Close();

		void Resize(UINT width, UINT height);

		UINT GetWidth() const;
		UINT GetHeight() const;
		bool IsVsync() const;
		void SetVsync(bool enable);

	private:
		GLFWwindow* _window = nullptr;
		WindowData _data{};
		static inline Window* _instance = nullptr;
		static inline bool _GLFWinitialized = false;
		static inline bool _GLADinitialized = false;
	};
}