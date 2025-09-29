module;
#include "OpenGL.h"
module Render;
import :Shader;
import :ShaderCompiler;
import Math;

using namespace Vega::Math;

namespace Vega {

	Shader::Shader(std::string pathVertex, std::string pathFrag) : _pathVertex("res/" + pathVertex), _pathFrag("res/" + pathFrag) {
		SetID(CreateProgram(_pathVertex, _pathFrag));
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

	void Shader::SetVariable(std::string name, int value) {
		Use();
		glUniform1i(glGetUniformLocation(_ID, name.data()), value);
	}
	void Shader::SetVariable(std::string name, int2& value) {
		Use();
		glUniform2i(glGetUniformLocation(_ID, name.data()), value[0], value[1]);
	}
	void Shader::SetVariable(std::string name, int3& value) {
		Use();
		glUniform3i(glGetUniformLocation(_ID, name.data()), value[0], value[1], value[2]);
	}
	void Shader::SetVariable(std::string name, int4& value) {
		Use();
		glUniform4i(glGetUniformLocation(_ID, name.data()), value[0], value[1], value[2], value[3]);
	}

	void Shader::SetVariable(std::string name, float value) {
		Use();
		glUniform1f(glGetUniformLocation(_ID, name.data()), value);
	}
	void Shader::SetVariable(std::string name, float2& value) {
		Use();
		glUniform2f(glGetUniformLocation(_ID, name.data()), value[0], value[1]);
	}
	void Shader::SetVariable(std::string name, float3& value) {
		Use();
		glUniform3f(glGetUniformLocation(_ID, name.data()), value[0], value[1], value[2]);
	}
	void Shader::SetVariable(std::string name, float4& value) {
		Use();
		glUniform4f(glGetUniformLocation(_ID, name.data()), value[0], value[1], value[2], value[3]);
	}

	void Shader::SetInt(std::string variable, int value) {
		Use();
		glUniform1i(glGetUniformLocation(_ID, variable.data()), value);
	}
	void Shader::SetInt2(std::string variable, int2 vec) {
		Use();
		glUniform2i(glGetUniformLocation(_ID, variable.data()), vec[0], vec[1]);
	}
	void Shader::SetInt3(std::string variable, int3 vec) {
		Use();
		glUniform3i(glGetUniformLocation(_ID, variable.data()), vec[0], vec[1], vec[2]);
	}
	void Shader::SetInt4(std::string variable, int4 vec) {
		Use();
		glUniform4i(glGetUniformLocation(_ID, variable.data()), vec[0], vec[1], vec[2], vec[4] );
	}

	void Shader::SetFloat(std::string variable, float value) {
		Use();
		glUniform1f(glGetUniformLocation(_ID, variable.data()), value);
	}
	void Shader::SetFloat2(std::string variable, float2 vec) {
		Use();
		glUniform2f(glGetUniformLocation(_ID, variable.data()), vec[0], vec[1]);
	}
	void Shader::SetFloat3(std::string variable, float3 vec) {
		Use();
		glUniform3f(glGetUniformLocation(_ID, variable.data()), vec[0], vec[1], vec[2]);
	}
	void Shader::SetFloat4(std::string variable, float4 vec) {
		Use();
		glUniform4f(glGetUniformLocation(_ID, variable.data()), vec[0], vec[1], vec[2], vec[3]);
	}

	void Shader::SetMat3x3(std::string variable, const Math::Mat3x3f& matrix, bool transpose) {
		Use();
		glUniformMatrix3fv(glGetUniformLocation(_ID, variable.data()), 1, GL_TRUE, &matrix.a1);
	}


	//void Shader::AttachFloatRef(std::string& variable, float* data, int count) {
	//	_floatVariables.push_back({ variable, count, data });
	//}

	//void Shader::AttachIntRef(std::string& variable, int* data, int count) {
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
