#include "Window.h"
#include "Log.h"


namespace Vega {
	Window::Window() {
		Window::_instance = this;
	}

	Window::~Window() {
		Close();
		gladLoaderUnloadGL();
		glfwTerminate();
		_GLFWinitialized = false;
	}

	Window* Window::Get() {
		if (!(bool)Window::_instance) {
			spdlog::warn("No window created");
		}
		return Window::_instance;
	}

	GLFWwindow* Window::GetGLFWWindow() {
		return _window;
	}

	GLFWwindow* Window::Create(const WindowData& props) {
		if ((bool)_window) {
			spdlog::warn(std::format("Window already created '{}', returning first instance", _data.name));
			return _window;
		}

		if (!_GLFWinitialized) {
			int result = glfwInit();

			if (!(bool)result) {
				spdlog::critical("GLFW initialization failed");
				return nullptr;
			}

			spdlog::info("Successfully initialized GLFW");
			Window::_GLFWinitialized = true;
		}

		_window = glfwCreateWindow((int)props.width, (int)props.height, props.name, nullptr, nullptr);
		if (!(bool)_window) {
			spdlog::critical("Window creation failed");
			return nullptr;
		}
		_data = props;

		glfwMakeContextCurrent(_window);

		if (!_GLADinitialized) {
			int result = gladLoadGL(glfwGetProcAddress);

			if (!(bool)result) {
				spdlog::critical("GLAD initialization failed");
				return nullptr;
			}

			spdlog::info("Successfully initialized GLAD");
			Window::_GLADinitialized = true;
		}

		glfwSwapInterval((int)props.vsync);

		spdlog::info(std::format("Constructed window '{}' with size ({},{})", props.name, props.width, props.height));

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);

		return _window;
	}

	void Window::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(_window);
		glFinish();
	}

	void Window::Close() {
		if (!(bool)Window::_instance) return;

		glfwDestroyWindow(_window);
		_window = nullptr;
		Window::_instance = nullptr;
		spdlog::info(std::format("Closed window '{}'", _data.name));
	}

	void Window::Resize(UINT width, UINT height) {
		_data.width = width;
		_data.height = height;
	}

	UINT Window::GetWidth() const {
		return _data.width;
	}
	UINT Window::GetHeight() const {
		return _data.height;
	}
	bool Window::IsVsync() const {
		return _data.vsync;
	}
	void Window::SetVsync(bool enable) {
		glfwSwapInterval((int)enable);
		_data.vsync = enable;
	}
} // namespace Vega