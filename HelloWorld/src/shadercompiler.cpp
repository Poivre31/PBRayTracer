#include "shadercompiler.h"
#include <vector>
#include <fstream>
#include <iostream>

unsigned int CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//int result;
	//glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	//if (result == GL_FALSE)
	//{
	//	int length;
	//	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
	//	char* message = new char[length];
	//	glGetShaderInfoLog(id, length, &length, message);

	//	switch (type) {
	//	case(GL_VERTEX_SHADER):
	//		printf("Failed to compile vertex shader\n");
	//		break;
	//	case(GL_FRAGMENT_SHADER):
	//		printf("Failed to compile fragment shader\n");
	//		break;
	//	case(GL_COMPUTE_SHADER):
	//		printf("Failed to compile compute shader\n");
	//		break;
	//	}

	//	printf("%s \n", message);
	//	glDeleteShader(id);
	//	return 0;
	//}

	return id;
}

int CreateComputeShader(const std::string& path) {
	std::ifstream stream(path);
	std::stringstream source;
	std::string line;

	while (getline(stream, line)) {
		source << line << "\n";
	}

	unsigned int program = glCreateProgram();
	unsigned int cs = CompileShader(GL_COMPUTE_SHADER, source.str());

	glAttachShader(program, cs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(cs);

	return program;
}

int CreateComputeShader(const std::vector<std::string>& pathList) {
	std::ifstream stream;
	std::stringstream source;
	std::string line;
	unsigned int program = glCreateProgram();
	std::vector<unsigned int> shaderList(pathList.size());

	int i = 0;
	int success;
	//std::ofstream outFile;
	//outFile.open("Shader.txt");
	for (std::string path : pathList)
	{
		bool skipping = false;
		stream = std::ifstream(path);
		while (getline(stream, line)) {
			//if (line.contains("#version") && i!=0) continue;
			if (line.contains("//SKIP") || skipping) skipping = true;
			if (line.contains("//ENDSKIP")) skipping = false;
			if (!skipping) {
				source << line << "\n";
				//outFile << line << "\n";
			}
		}
		shaderList[i] = CompileShader(GL_COMPUTE_SHADER, source.str());
		glGetShaderiv(shaderList[i], GL_LINK_STATUS, &success);
		if (!success) {
			int length;
			glGetShaderiv(shaderList[i], GL_INFO_LOG_LENGTH, &length);
			char* message = new char[length];
			glGetShaderInfoLog(shaderList[i], length, &length, message);
			std::cerr << "ERROR::PROGRAM::SHADER " << i << " FAILED\n" << message << std::endl;
		}
		glAttachShader(program, shaderList[i]);
		source.str("");
		i++;
	}
	//outFile.close();

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[4096];
		glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
		std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
	if (!success) {
		char infoLog[4096];
		glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
		std::cerr << "ERROR::PROGRAM::VALIDATION_FAILED\n" << infoLog << std::endl;
	}

	for (auto shader : shaderList) {
		glDeleteShader(shader);
	}

	return program;
}

int CreateShader(const std::string& vertexPath, const std::string& fragPath) {
	std::ifstream stream(vertexPath);
	std::stringstream vertexSource;
	std::stringstream fragSource;
	std::string line;

	while (getline(stream, line)) {
		vertexSource << line << "\n";
	}

	stream = std::ifstream(fragPath);
	while (getline(stream, line)) {
		fragSource << line << "\n";
	}

	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSource.str());
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragSource.str());

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}