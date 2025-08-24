#pragma once
#include "spdlog/spdlog.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#ifdef DEBUG
#define V_LOG_LEVEL 0
#elifdef RELEASE
#define V_LOG_LEVEL 0
#elifdef DIST
#define V_LOG_LEVEL 4
#endif

namespace Vega {

	void SetLogLevel();

	void GLAPIENTRY MessageCallback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam
	);

}


