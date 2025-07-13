#pragma once
#include "shadercompiler.h"
#include <iostream>
class Shader {
public:
	unsigned int ID;

	Shader(const char* pathVertex, const char* pathFrag) {
		ID = CreateShader(pathVertex, pathFrag);
	}

	Shader() { ID = 0; }

	//~Shader() {
	//	glDeleteProgram(ID);
	//}

	void Use() const {
		glUseProgram(ID);
	}

	void SetInt(const char* variable, int value) const {
		glUniform1i(glGetUniformLocation(ID, variable), value);
	}

	void SetInt2(const char* variable, int a, int b) const {
		glUniform2i(glGetUniformLocation(ID, variable), a, b);
	}

	void SetInt3(const char* variable, int a, int b, int c) const {
		glUniform3i(glGetUniformLocation(ID, variable), a, b, c);
	}

	void SetFloat(const char* variable, float value) const {
		glUniform1f(glGetUniformLocation(ID, variable), value);
	}

	void SetFloat2(const char* variable, float a, float b) const {
		glUniform2f(glGetUniformLocation(ID, variable), a, b);
	}

	void SetFloat3(const char* variable, float a, float b, float c) const {
		glUniform3f(glGetUniformLocation(ID, variable), a, b, c);
	}
};

class ComputeShader : public Shader {
public:
	ComputeShader(const char* path) {
		ID = CreateComputeShader(path);
	}

	void Dispatch(int res, int numThread) {
		glDispatchCompute((res + numThread - 1) / numThread, 1, 1);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
	};

	void Dispatch(int resX, int resY, int numThreadX, int numThreadY) {
		glDispatchCompute((resX + numThreadX - 1) / numThreadX, (resY + numThreadY - 1) / numThreadY, 1);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
	};

	void Dispatch(int resX, int resY, int resZ, int numThreadX, int numThreadY, int numThreadZ) const {
		glDispatchCompute((resX + numThreadX - 1) / numThreadX, (resY + numThreadY - 1) / numThreadY, (resZ + numThreadZ - 1) / numThreadZ);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
	};
};