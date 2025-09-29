module;
#include "OpenGL.h"
module Render;
import :ShaderCompiler;
import std;
import Utility;

namespace Vega {
	static void ErrorLog(GLuint program, GLenum statusCheck, const char* errorMessage) {
		int success = 0;
		glGetProgramiv(program, statusCheck, &success);
		if (!success) {
			int length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
			std::unique_ptr<char> message = std::make_unique<char>(length);
			glGetProgramInfoLog(program, length, nullptr, message.get());
			Log.error(errorMessage);
			Log.error(message.get());
		}
	}

	GLuint CompileShader(unsigned int type, const std::string& source) {
		GLuint id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			int length = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = new char[length];
			glGetShaderInfoLog(id, length, &length, message);

			switch (type) {
			case(GL_VERTEX_SHADER):
				Log.error("Failed to compile vertex shader");
				break;
			case(GL_FRAGMENT_SHADER):
				Log.error("Failed to compile fragment shader");
				break;
			case(GL_COMPUTE_SHADER):
				Log.error("Failed to compile compute shader");
				break;
			default:
				Log.error("Failed to compile 'unknown type' shader");
			}

			Log.info(message);
			glDeleteShader(id);

			return id;
		}

		return id;
	}

	GLuint CreateComputeProgram(const std::vector<std::string>& pathList) {
		std::ifstream stream;
		std::stringstream source;
		std::string line;
		GLuint program = glCreateProgram();
		std::vector<GLuint> shaderList(pathList.size());

		int i = 0;
		for (std::string path : pathList)
		{
			stream = std::ifstream(path);
			if (!stream) {
				Vega::Log.error(std::format("Invalid compute shader file path: {}, aborting program creation", path));
				return 0;
			}
			while (getline(stream, line)) {
				source << line << "\n";
			}
			shaderList[i] = CompileShader(GL_COMPUTE_SHADER, source.str());
			glAttachShader(program, shaderList[i]);
			source.str("");
			i++;
		}

		glLinkProgram(program);
		ErrorLog(program, GL_LINK_STATUS, "Program linking failed");

		glValidateProgram(program);
		ErrorLog(program, GL_VALIDATE_STATUS, "Program validation failed");

		for (auto shader : shaderList) {
			glDeleteShader(shader);
		}

		return program;
	}

	GLuint CreateProgram(const std::string& vertPath, const std::string& fragPath) {
		std::ifstream stream;
		std::stringstream source;
		std::string line;
		GLuint program = glCreateProgram();

		stream = std::ifstream(vertPath);
		if (!stream) {
			Vega::Log.error(std::format("Invalid vertex shader file path: {}, aborting program creation", vertPath));
			return 0;
		}
		while (getline(stream, line)) {
			source << line << "\n";
		}
		GLuint vertShader = CompileShader(GL_VERTEX_SHADER, source.str());
		glAttachShader(program, vertShader);
		source.str("");

		stream = std::ifstream(fragPath);
		if (!stream) {
			Vega::Log.error(std::format("Invalid fragment shader file path: {}, aborting program creation", fragPath));
			return 0;
		}
		while (getline(stream, line)) {
			source << line << "\n";
		}
		GLuint fragShader = CompileShader(GL_FRAGMENT_SHADER, source.str());
		glAttachShader(program, fragShader);

		glLinkProgram(program);
		ErrorLog(program, GL_LINK_STATUS, "Program linking failed");

		glValidateProgram(program);
		ErrorLog(program, GL_VALIDATE_STATUS, "Program validation failed");

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);

		return program;
	}
}
