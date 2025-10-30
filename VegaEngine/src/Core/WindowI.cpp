module;
#include <glad/gl.h>
#include <GLFW/glfw3.h>

module Core;
import Utility;

namespace Vega {

	Window::Window() = default;

	Window::~Window() {
		if ((bool)_window) {
			Log.warn("Calling window destructor but window hasn't been shut down");
		}
		glfwTerminate();
		_GLFWinitialized = false;
	}

	GLFWwindow* Window::GetGLFWWindow() {
		return _window;
	}

	GLFWwindow* Window::Create(const WindowData& props) {
		if ((bool)_window) {
			Log.warn(std::format("Window already created '{}', returning first instance", _data.name));
			return _window;
		}

		if (!_GLFWinitialized) {
			int result = glfwInit();

			if (!(bool)result) {
				Log.error("GLFW initialization failed");
				return nullptr;
			}

			Log.debug("Successfully initialized GLFW");
			_GLFWinitialized = true;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

		_window = glfwCreateWindow((int)props.width, (int)props.height, props.name, nullptr, nullptr);
		if (!(bool)_window) {
			Log.error("Window creation failed");
			return nullptr;
		}

		glfwMakeContextCurrent(_window);

		if (!_GLADinitialized) {
			int result = gladLoadGL(glfwGetProcAddress);

			if (!(bool)result) {
				Log.error("GLAD initialization failed");
				return nullptr;
			}

			Log.debug("Successfully initialized GLAD");
			_GLADinitialized = true;
		}

		_data = props;

		glfwSwapInterval((int)props.vsync);

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);

		glClearColor(1, 0, 1, 1);

		glfwSetWindowCloseCallback(_window, CloseEvent);
		glfwSetWindowSizeCallback(_window, ResizeEvent);

		Log.info(std::format("Constructed window '{}' with size ({},{})", props.name, props.width, props.height));

		return _window;
	}

	void Window::OnUpdate() {
		if (!(bool)_window) {
			Log.error("Trying to update a non initialised window");
			return;
		}

		glfwPollEvents();
		glViewport(0, 0, (GLsizei)_data.width, (GLsizei)_data.height);
		glfwSwapBuffers(_window);
		glFinish();
	}

	void Window::Shutdown() {
		if (!(bool)_window) {
			Log.error("Trying to shutdow a non initialised window");
			return;
		}

		glfwDestroyWindow(_window);
		_window = nullptr;
		gladLoaderUnloadGL();
		_GLADinitialized = false;

		Log.debug(std::format("Closed window '{}'", _data.name));
	}

	void Window::Resize(int width, int height) {
		_data.width = width;
		_data.height = height;
	}

	void Window::CenterCursor(bool enable) {
		if (enable) {
			glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else {
			glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	int Window::Width() const {
		return _data.width;
	}
	int Window::Height() const {
		return _data.height;
	}
	bool Window::IsVsync() const {
		return _data.vsync;
	}
	void Window::SetVsync(bool enable) {
		glfwSwapInterval((int)enable);
		_data.vsync = enable;
	}
}