#include "Shader.h"
#include <span>

namespace Vega {

	Shader::Shader(const char* pathVertex, const char* pathFrag) : _pathVertex(pathVertex), _pathFrag(pathFrag) {
		SetID(CreateProgram(pathVertex, pathFrag));
	}

	Shader::~Shader() {
		glDeleteProgram(_ID);
	}


	void Shader::Reload() {
		SetID(CreateProgram(_pathVertex, _pathFrag));
	}

	void Shader::Use() const {
		glUseProgram(_ID);
	}

	GLuint Shader::GetID() {
		return _ID;
	}

	void Shader::SetID(GLuint ID) {
		_ID = ID;
	}

	void Shader::SetInt(const char* variable, int value) {
		Use();
		glUniform1i(glGetUniformLocation(_ID, variable), value);
	}

	void Shader::SetInt2(const char* variable, int a, int b) {
		Use();
		glUniform2i(glGetUniformLocation(_ID, variable), a, b);
	}
	void Shader::SetInt2(const char* variable, std::span<const int,2> adress) {
		Use();
		glUniform2i(glGetUniformLocation(_ID, variable), adress[0], adress[1]);
	}

	void Shader::SetInt3(const char* variable, int a, int b, int c) {
		Use();
		glUniform3i(glGetUniformLocation(_ID, variable), a, b, c);
	}
	void Shader::SetInt3(const char* variable, std::span<const int,3> adress) {
		Use();
		glUniform3i(glGetUniformLocation(_ID, variable), adress[0], adress[1], adress[2]);
	}

	void Shader::SetFloat(const char* variable, float value) {
		Use();
		glUniform1f(glGetUniformLocation(_ID, variable), value);
	}

	void Shader::SetFloat2(const char* variable, float a, float b) {
		Use();
		glUniform2f(glGetUniformLocation(_ID, variable), a, b);
	}
	void Shader::SetFloat2(const char* variable, std::span<const float,2> adress) {
		Use();
		glUniform2f(glGetUniformLocation(_ID, variable), adress[0], adress[1]);
	}

	void Shader::SetFloat3(const char* variable, float a, float b, float c) {
		Use();
		glUniform3f(glGetUniformLocation(_ID, variable), a, b, c);
	}
	void Shader::SetFloat3(const char* variable, std::span<const float,3> adress) {
		Use();
		glUniform3f(glGetUniformLocation(_ID, variable), adress[0], adress[1], adress[2]);
	}

	void Shader::SetMat3x3(const char* variable, float* adress, bool transpose) {
		Use();
		glUniformMatrix3fv(glGetUniformLocation(_ID, variable),1,GL_TRUE,adress);
	}


	//void Shader::AttachFloatRef(const char* variable, float* data, int count) {
	//	_floatVariables.push_back({ variable, count, data });
	//}

	//void Shader::AttachIntRef(const char* variable, int* data, int count) {
	//	_intVariables.push_back({ variable, count, data });
	//}

	//void Shader::UpdateUniforms() {
	//	Use();
	//	for (const ShaderInt& variable : _intVariables) {
	//		GLint location = glGetUniformLocation(_ID, variable.variableName);
	//		int* adress = variable.adress;
	//		switch (variable.count) {
	//		case(1):
	//			glUniform1i(location, adress[0]);
	//			break;
	//		case(2):
	//			glUniform2i(location, adress[0], adress[1]);
	//			break;
	//		case(3):
	//			glUniform3i(location, adress[0], adress[1], adress[2]);
	//			break;
	//		case(4):
	//			glUniform4i(location, adress[0], adress[1], adress[2], adress[3]);
	//			break;
	//		}
	//	}

	//	for (const ShaderFloat& variable : _floatVariables) {
	//		GLint location = glGetUniformLocation(_ID, variable.variableName);
	//		float* adress = variable.adress;
	//		switch (variable.count) {
	//		case(1):
	//			glUniform1f(location, adress[0]);
	//			break;
	//		case(2):
	//			glUniform2f(location, adress[0], adress[1]);
	//			break;
	//		case(3):
	//			glUniform3f(location, adress[0], adress[1], adress[2]);
	//			break;
	//		case(4):
	//			glUniform4f(location, adress[0], adress[1], adress[2], adress[3]);
	//			break;
	//		}
	//	}
	//}

}
