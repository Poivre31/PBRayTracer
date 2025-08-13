#include "screenQuad.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

ScreenQuad::ScreenQuad(Shader* screenShader) : screenShader(screenShader) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const float*)(2 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ScreenQuad::Draw(Renderer& UI, unsigned int textureIndex) const {

	screenShader->Use();
	screenShader->SetInt("screenTexture", textureIndex);

	glBindVertexArray(vao);
	glDisable(GL_DEPTH_TEST);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(UI.window);
	glFinish();
}

void ScreenQuad::Reload() {
	screenShader->Reload();
}