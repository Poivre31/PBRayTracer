#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/fmt/bundled/color.h"
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

namespace Log {

	enum class Color : uint8_t {

		Black_L = (uint8_t)fmt::terminal_color::bright_black,
		Blue_L = (uint8_t)fmt::terminal_color::bright_blue,
		Cyan_L = (uint8_t)fmt::terminal_color::bright_cyan,
		Green_L = (uint8_t)fmt::terminal_color::bright_green,
		Magneta_L = (uint8_t)fmt::terminal_color::bright_magenta,
		Red_L = (uint8_t)fmt::terminal_color::bright_red,
		White_L = (uint8_t)fmt::terminal_color::bright_white,
		Yellow_L = (uint8_t)fmt::terminal_color::bright_yellow,
		Black = (uint8_t)fmt::terminal_color::black,
		Blue = (uint8_t)fmt::terminal_color::blue,
		Cyan = (uint8_t)fmt::terminal_color::cyan,
		Green = (uint8_t)fmt::terminal_color::green,
		Magenta = (uint8_t)fmt::terminal_color::magenta,
		Red = (uint8_t)fmt::terminal_color::red,
		White = (uint8_t)fmt::terminal_color::white,
		Yellow = (uint8_t)fmt::terminal_color::yellow,
	};

	inline void trace(const std::string& message, Color color = Color::White) {
		spdlog::trace(fmt::format(fmt::fg(fmt::terminal_color(color)), fmt::runtime(message)));
	}

	inline void info(const std::string& message, Color color = Color::Green_L) {
		spdlog::info(fmt::format(fmt::fg(fmt::terminal_color(color)), fmt::runtime(message)));
	}

	inline void debug(const std::string& message, Color color = Color::Cyan_L) {
		spdlog::debug(fmt::format(fmt::fg(fmt::terminal_color(color)), fmt::runtime(message)));
	}

	inline void warn(const std::string& message, Color color = Color::Yellow_L) {
		spdlog::warn(fmt::format(fmt::fg(fmt::terminal_color(color)), fmt::runtime(message)));
	}

	inline void error(const std::string& message, Color color = Color::Red_L) {
		spdlog::error(fmt::format(fmt::fg(fmt::terminal_color(color)), fmt::runtime(message)));
	}

	inline void critical(const std::string& message, Color color = Color::White) {
		spdlog::critical(fmt::format(fmt::fg(fmt::terminal_color(color)), fmt::runtime(message)));
	}

}


