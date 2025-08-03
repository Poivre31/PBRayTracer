#include "shader.h"


Shader::Shader(const char* pathVertex, const char* pathFrag) : pathVertex(pathVertex), pathFrag(pathFrag) {
	ID = CreateShader(pathVertex, pathFrag);
}

Shader::Shader() { ID = 0; pathVertex = nullptr; pathFrag = nullptr; }


void Shader::Reload() {
	ID = CreateShader(pathVertex, pathFrag);
}

void Shader::Use() const {
	glUseProgram(ID);
}

void Shader::SetInt(const char* variable, int value) const {
	Use();
	glUniform1i(glGetUniformLocation(ID, variable), value);
}

void Shader::SetInt2(const char* variable, int a, int b) const {
	Use();
	glUniform2i(glGetUniformLocation(ID, variable), a, b);
}

void Shader::SetInt3(const char* variable, int a, int b, int c) const {
	Use();
	glUniform3i(glGetUniformLocation(ID, variable), a, b, c);
}

void Shader::SetFloat(const char* variable, float value) const {
	Use();
	glUniform1f(glGetUniformLocation(ID, variable), value);
}

void Shader::SetFloat2(const char* variable, float a, float b) const {
	Use();
	glUniform2f(glGetUniformLocation(ID, variable), a, b);
}

void Shader::SetFloat3(const char* variable, float a, float b, float c) const {
	Use();
	glUniform3f(glGetUniformLocation(ID, variable), a, b, c);
}
