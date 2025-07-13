#pragma once
#include "shadercompiler.h"
#include <GLFW/glfw3.h>
#include "shader.h"
#include <iostream>
class ScreenQuad {
public:
	ScreenQuad(Shader* screenShader): screenShader(screenShader) {
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const float*)(2 * sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Draw(unsigned int textureIndex) const {
		screenShader->Use();
		screenShader->SetInt("screenTexture", textureIndex);

		glDrawArrays(GL_TRIANGLES, 0,3);
	}

private:
	float vertices[12] = {
		-1.f,-3.f,0.f,-1.f,
		-1.f,1.f,0.f,1.f,
		3.f,1.f,2.f,1.f,
	};

	unsigned int vertexBuffer;
	Shader* screenShader;
};