module;

#include <glad/gl.h>
#include <GLFW/glfw3.h>

export module Core:Log;
import :Timer;
import std;

namespace Vega {

	export const enum class Color {
		Black,
		Blue,
		Cyan,
		Green,
		Purple,
		Red,
		White,
		Yellow,
		BlackLight,
		BlueLight,
		CyanLight,
		GreenLight,
		PurpleLight,
		RedLight,
		WhiteLight,
		YellowLight,
		ColorsCount,
	};

	static std::string GetAnsiCode(Color color) {
		switch (color) {
			case Color::Black:
				return "\033[30m";
			case Color::Red:
				return "\033[31m";
			case Color::Green:
				return "\033[32m";
			case Color::Yellow:
				return "\033[33m";
			case Color::Blue:
				return "\033[34m";
			case Color::Purple:
				return "\033[35m";
			case Color::Cyan:
				return "\033[36m";
			case Color::White:
				return "\033[37m";
			case Color::BlackLight:
				return "\033[90m";
			case Color::RedLight:
				return "\033[91m";
			case Color::GreenLight:
				return "\033[92m";
			case Color::YellowLight:
				return "\033[93m";
			case Color::BlueLight:
				return "\033[94m";
			case Color::PurpleLight:
				return "\033[95m";
			case Color::CyanLight:
				return "\033[96m";
			case Color::WhiteLight:
				return "\033[97m";
			default:
				return "\033[0m";
		}
	}

	export const enum class LogLevel {
		Trace,
		Info,
		Debug,
		Warn,
		Error,
		LevelsCount,
	};

}


namespace Vega {

	export class Logger {
	public:
		Logger(const std::string& designator, Color color) : _designator(designator), _desColor(color) {
			std::ranges::fill(_logLevel, true);
		}

		void trace(const std::string& message, Color color = Color::White) {
			if (!_logLevel[(int)LogLevel::Trace])
				return;
			PrintMessage(message, color);
		}

		void info(const std::string& message, Color color = Color::GreenLight) {
			if (!_logLevel[(int)LogLevel::Info])
				return;
			PrintMessage(message, color);
		}

		void debug(const std::string& message, Color color = Color::CyanLight) {
			if (!_logLevel[(int)LogLevel::Debug])
				return;
			PrintMessage(message, color);
		}

		void warn(const std::string& message, Color color = Color::YellowLight) {
			if (!_logLevel[(int)LogLevel::Warn])
				return;
			PrintMessage(message, color);
		}

		void error(const std::string& message, Color color = Color::RedLight) {
			if (!_logLevel[(int)LogLevel::Error])
				return;
			PrintMessage(message, color);
		}
		
		
		void EnableLogLevel(LogLevel level, bool enabled) {
			_logLevel[(int)level] = enabled;
		}


	private:
		void PrintMessage(const std::string& message, Color color) {
			std::println(
				"{}{:%d-%m-%y %H:%M:%S}\033[0m [{}{}\033[0m] {}{}\033[0m",
				GetAnsiCode(Color::BlackLight), Timer::GetZoneTime(),
				GetAnsiCode(_desColor), _designator,
				GetAnsiCode(color), message
			);
		}

		const std::string _designator;
		Color _desColor;
		std::array<bool,(int)LogLevel::LevelsCount> _logLevel;
	};

	export Logger Log("Vega", Color::Yellow);

	export void GLAPIENTRY MessageCallback(
		GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam
	) {
		if (type == GL_DEBUG_TYPE_ERROR) {
			Log.error(std::format("[GL ERROR]: {}", message));
		}
	}
}