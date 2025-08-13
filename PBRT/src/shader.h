#pragma once
#include "shadercompiler.h"
#include <iostream>

class Shader {
public:
	unsigned int ID;

	Shader(const char* pathVertex, const char* pathFrag);
	Shader();

	virtual void Reload();
	void Use() const;

	void SetInt(const char* variable, int value) const;
	void SetInt2(const char* variable, int a, int b) const;
	void SetInt3(const char* variable, int a, int b, int c) const;

	void SetFloat(const char* variable, float value) const;
	void SetFloat2(const char* variable, float a, float b) const;
	void SetFloat3(const char* variable, float a, float b, float c) const;
private:
	const char* pathVertex;
	const char* pathFrag;
};