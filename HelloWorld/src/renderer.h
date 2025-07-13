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
	bool vsync;

	Renderer(const char* windowName, size_t width, size_t height, bool vsync = true) : width(width), height(height), vsync(vsync), io(0), style(0) {
		if (!glfwInit()) exit(-1);

		window = glfwCreateWindow(width, height, windowName, nullptr, nullptr);

		assert(("Window creation failed for: ", window));

		glfwMakeContextCurrent(window);
		glfwSwapInterval(vsync);
	}

	void Setup() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		io = &ImGui::GetIO(); (void)io;
		io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::StyleColorsDark();

		style = &ImGui::GetStyle();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	void Update() const {
		glfwPollEvents();
		glfwSwapInterval(vsync);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
};