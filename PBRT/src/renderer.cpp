#include "renderer.h"
#include "log.h"

Renderer::Renderer(const char* windowName, size_t width, size_t height, bool vsync) : width(width), height(height), vsync(vsync), io(0), style(0) {
	if (!glfwInit()) Log::Error("GLFW init failed");

	window = glfwCreateWindow(width, height , windowName, nullptr, nullptr);

	if (!window) Log::Error("Window creation failed");

	glfwMakeContextCurrent(window);
	glfwMakeContextCurrent(window);

	GLint profileMask = 0;
	glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profileMask);

	if (profileMask & GL_CONTEXT_CORE_PROFILE_BIT)
		printf("OpenGL Context Profile: Core\n");
	else if (profileMask & GL_CONTEXT_COMPATIBILITY_PROFILE_BIT)
		printf("OpenGL Context Profile: Compatibility\n");
	else
		printf("OpenGL Context Profile: Unknown/None\n");

	glfwSwapInterval(vsync);
}

void Renderer::Setup() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	style = &ImGui::GetStyle();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void Renderer::Close() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void Renderer::Update(int& imageWidth, int& imageHeight) {
	width = imageWidth;
	height = imageHeight;
	glfwPollEvents();
	glfwSwapInterval(vsync);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	glfwGetFramebufferSize(window, &imageWidth, &imageHeight);
	glViewport(0, 0, imageWidth, imageHeight);
	glClearColor(1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}
