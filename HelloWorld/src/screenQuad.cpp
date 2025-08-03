#include "screenQuad.h"

ScreenQuad::ScreenQuad(Shader* screenShader) : screenShader(screenShader) {
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const float*)(2 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ScreenQuad::Draw(unsigned int textureIndex) const {
	screenShader->Use();
	screenShader->SetInt("screenTexture", textureIndex);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void ScreenQuad::Reload() {
	screenShader->Reload();
}