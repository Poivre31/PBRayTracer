#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include "GL/glew.h"
#include <GLFW/glfw3.h>

class Renderer {
public:
	size_t width;
	size_t height;
	GLFWwindow* window;
	ImGuiIO* io;
	ImGuiStyle* style;
	bool vsync = true;
	bool showDemo = false;
	float ditherStrength = 0.007f;
	bool doRender = true;

	Renderer(const char* windowName, size_t width, size_t height, bool vsync = true);

	void Setup();

	void Update(int& imageWidth, int& imageHeight);

	void Close();
};