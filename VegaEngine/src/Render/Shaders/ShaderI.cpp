module;
#include "OpenGL.h"
module Render;
import :Shader;
import :ShaderCompiler;
import Math;
import Utility;


namespace Vega {

	Shader::Shader(const char* pathVertex, const char* pathFrag) : _pathVertex("res/" + std::string(pathVertex)), _pathFrag("res/" + std::string(pathFrag)) {
		SetID(CreateProgram(_pathVertex.data(), _pathFrag.data()));
	}

	Shader::~Shader() {
		glDeleteProgram(_ID);
	}


	void Shader::Reload() {
		SetID(CreateProgram(_pathVertex.data(), _pathFrag.data()));
	}

	void Shader::Use() const {
		if (!_ID) {
			Log.error("Trying to use unexisting shader");
		}
		glUseProgram(_ID);
	}

	GLuint Shader::GetID() {
		return _ID;
	}

	void Shader::SetID(GLuint ID) {
		_ID = ID;
	}

	void Shader::SetVariable(const char* name, int value) {
		Use();
		glUniform1i(glGetUniformLocation(_ID, name), value);
	}
	void Shader::SetVariable(const char* name, int2& value) {
		Use();
		glUniform2i(glGetUniformLocation(_ID, name), value[0], value[1]);
	}
	void Shader::SetVariable(const char* name, int3& value) {
		Use();
		glUniform3i(glGetUniformLocation(_ID, name), value[0], value[1], value[2]);
	}
	void Shader::SetVariable(const char* name, int4& value) {
		Use();
		glUniform4i(glGetUniformLocation(_ID, name), value[0], value[1], value[2], value[3]);
	}

	void Shader::SetVariable(const char* name, float value) {
		Use();
		glUniform1f(glGetUniformLocation(_ID, name), value);
	}
	void Shader::SetVariable(const char* name, float2& value) {
		Use();
		glUniform2f(glGetUniformLocation(_ID, name), value[0], value[1]);
	}
	void Shader::SetVariable(const char* name, float3& value) {
		Use();
		glUniform3f(glGetUniformLocation(_ID, name), value[0], value[1], value[2]);
	}
	void Shader::SetVariable(const char* name, float4& value) {
		Use();
		glUniform4f(glGetUniformLocation(_ID, name), value[0], value[1], value[2], value[3]);
	}

	void Shader::SetVariable(const char* name, double value) {
		Use();
		glUniform1d(glGetUniformLocation(_ID, name), value);
	}

	void Shader::SetInt(const char* variable, int value) {
		Use();
		glUniform1i(glGetUniformLocation(_ID, variable), value);
	}
	void Shader::SetInt2(const char* variable, int2 vec) {
		Use();
		glUniform2i(glGetUniformLocation(_ID, variable), vec[0], vec[1]);
	}
	void Shader::SetInt3(const char* variable, int3 vec) {
		Use();
		glUniform3i(glGetUniformLocation(_ID, variable), vec[0], vec[1], vec[2]);
	}
	void Shader::SetInt4(const char* variable, int4 vec) {
		Use();
		glUniform4i(glGetUniformLocation(_ID, variable), vec[0], vec[1], vec[2], vec[4] );
	}

	void Shader::SetFloat(const char* variable, float value) {
		Use();
		glUniform1f(glGetUniformLocation(_ID, variable), value);
	}
	void Shader::SetFloat2(const char* variable, float2 vec) {
		Use();
		glUniform2f(glGetUniformLocation(_ID, variable), vec[0], vec[1]);
	}
	void Shader::SetFloat3(const char* variable, float3 vec) {
		Use();
		glUniform3f(glGetUniformLocation(_ID, variable), vec[0], vec[1], vec[2]);
	}
	void Shader::SetFloat4(const char* variable, float4 vec) {
		Use();
		glUniform4f(glGetUniformLocation(_ID, variable), vec[0], vec[1], vec[2], vec[3]);
	}

	void Shader::SetMat3x3(const char* variable, const Mat3x3f& matrix, bool transpose) {
		Use();
		glUniformMatrix3fv(glGetUniformLocation(_ID, variable), 1, GL_TRUE, &matrix.a1);
	}


	//void Shader::AttachFloatRef(const char*& variable, float* data, int count) {
	//	_floatVariables.push_back({ variable, count, data });
	//}

	//void Shader::AttachIntRef(const char*& variable, int* data, int count) {
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
