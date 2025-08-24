#include "Shadercompiler.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "spdlog/spdlog.h"

GLuint CompileShader(unsigned int type, const std::string& source) {
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);

		switch (type) {
		case(GL_VERTEX_SHADER):
			spdlog::error("Failed to compile vertex shader");
			break;
		case(GL_FRAGMENT_SHADER):
			spdlog::error("Failed to compile fragment shader");
			break;
		case(GL_COMPUTE_SHADER):
			spdlog::error("Failed to compile compute shader");
			break;
		default:
			spdlog::error("Failed to compile 'unknown type' shader");
		}

		printf("%s \n", message);
		glDeleteShader(id);
		return id;
	}

	return id;
}

GLuint CreateComputeProgram(const std::vector<const char*>& pathList) {
	std::ifstream stream;
	std::stringstream source;
	std::string line;
	GLuint program = glCreateProgram();
	std::vector<GLuint> shaderList(pathList.size());

	int i = 0;
	int success = 0;
	for (std::string path : pathList)
	{
		stream = std::ifstream(path);
		while (getline(stream, line)) {
			source << line << "\n";
		}
		shaderList[i] = CompileShader(GL_COMPUTE_SHADER, source.str());
		glAttachShader(program, shaderList[i]);
		source.str("");
		i++;
	}

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetProgramInfoLog(program, length, nullptr, message);
		spdlog::error("Program linking failed: ");
		spdlog::error(message);
	}

	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
	if (!success) {
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetProgramInfoLog(program, length, nullptr, message);
		spdlog::error("Program linking failed: ");
		spdlog::error(message);
	}

	for (auto shader : shaderList) {
		glDeleteShader(shader);
	}

	return program;
}

GLuint CreateProgram(const char* vertPath, const char* fragPath) {
	std::ifstream stream;
	std::stringstream source;
	std::string line;
	GLuint program = glCreateProgram();

	int success = 0;
	stream = std::ifstream(vertPath);
	while (getline(stream, line)) {
		source << line << "\n";
	}
	GLuint vertShader = CompileShader(GL_VERTEX_SHADER, source.str());
	glAttachShader(program, vertShader);
	source.str("");

	stream = std::ifstream(fragPath);
	while (getline(stream, line)) {
		source << line << "\n";
	}
	GLuint fragShader = CompileShader(GL_FRAGMENT_SHADER, source.str());
	glAttachShader(program, fragShader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetProgramInfoLog(program, length, nullptr, message);
		spdlog::error("Program linking failed: ");
		spdlog::error(message);
	}

	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
	if (!success) {
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetProgramInfoLog(program, length, nullptr, message);
		spdlog::error("Program linking failed: ");
		spdlog::error(message);
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return program;
}