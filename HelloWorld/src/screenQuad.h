#pragma once
#include "shadercompiler.h"
#include <GLFW/glfw3.h>
#include "shader.h"
#include <iostream>
class ScreenQuad {
public:
	ScreenQuad(Shader* screenShader);

	void Draw(unsigned int textureIndex) const;

	void Reload();

private:
	float vertices[12] = {
		-1.f,-3.f,0.f,-1.f,
		-1.f,1.f,0.f,1.f,
		3.f,1.f,2.f,1.f,
	};

	unsigned int vertexBuffer;
	Shader* screenShader;
};