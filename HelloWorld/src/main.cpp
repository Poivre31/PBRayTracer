// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "shadercompiler.h"
#include "shader.h"
#include "screenQuad.h"
#include "renderer.h"
#include "postprocessing.h"
#include "texture.h"
#include "sphere.h"
#include "mathHelper.h"

#define M_PI 3.1415926535897932384626433832795

static float fov = 45;
static int kernelRadius = 0;
static bool Vsync = true;
static bool downsampleBlur = false;
static bool showDemo = false;
static float ditherStrength = 0;
static int noiseSteps = 10;
static int nSphere = 1;
static SphereBuffer spheresBuffer{};
static unsigned int ssbo = 0;

static void randomSpheres(std::vector<Sphere>& spheres, int nSpheres) {
	spheres.clear();
	//spheres->reserve(nSpheres);
	for (size_t i = 0; i < nSpheres; i++)
	{
		spheres.push_back(Sphere{ randF(4, 10), randF(-1, 1),randF(-2, 2), randF(.05, .2), randF(0, 1), randF(0, 1), randF(0, 1) });
	}
	spheresBuffer = parseSpheres(spheres);
	glNamedBufferSubData(ssbo, 0, sizeof(SphereBuffer), &spheresBuffer);
}
static void UIRender(Renderer& renderer, std::vector<Sphere>& spheres) {
	if (showDemo)
		ImGui::ShowDemoWindow(&showDemo);

	ImGui::Begin("Debug");
	//ImGui::SliderFloat3("Sphere position", sphere.position, 0, 50);
	//ImGui::SliderFloat("Sphere radius", &sphere.radius, 0, 5);
	//ImGui::SliderFloat3("Sphere color", sphere.color, 0, 1);
	if (ImGui::SliderInt("Number of spheres", &nSphere, 1, 256)) randomSpheres(spheres, nSphere);
	ImGui::SliderFloat("Vertical fov", &fov, 0, 90);
	ImGui::SliderInt("Kernel radius", &kernelRadius, 0, 25);
	ImGui::Checkbox("Show demo", &showDemo);
	ImGui::Checkbox("Vsync", &renderer.vsync);
	//ImGui::Checkbox("Downsample", &downsampleBlur);
	ImGui::SliderFloat("Dither strength", &ditherStrength, 0, .2);
	ImGui::SliderInt("Noise steps", &noiseSteps, 2, 100);
	ImGui::Text("Render time: %.3f ms/frame (%.1f FPS)", 1000.0f / renderer.io->Framerate, renderer.io->Framerate);
	ImGui::End();

	ImGui::Render();
}


int main(int, char**)
{
	Renderer UI = Renderer("Ray Tracing", 1920, 1080);
	glewInit();
	UI.Setup();

	int dataType = GL_RGBA16F;

	Texture screen = Texture(1920, 1080, dataType);
	Texture image = Texture(1920, 1080, dataType);

	ComputeShader computeShader = ComputeShader("res/shaders/sphere.comp");
	Shader shader = Shader("res/shaders/fullScreenQuad.vert", "res/shaders/fullScreenQuad.frag");

	ScreenQuad screenQuad = ScreenQuad(&shader);
	PostProcessor postProcess;

	std::vector<Sphere> spheres{};
	spheresBuffer = parseSpheres(spheres);
	randomSpheres(spheres, 1);
	//glBufferStorage(GL_SHADER_STORAGE_BUFFER, sizeof(SphereBuffer), nullptr,
	//	GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);

	//void* ptr = glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, size,
	//	GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);

	//// Copy directly
	//memcpy(ptr, &spheresBuffer, size);

	glGenBuffers(1, &ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(SphereBuffer), &spheresBuffer, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	while (!glfwWindowShouldClose(UI.window))
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		//glfwPollEvents();
		//glfwSwapInterval(UI.vsync);

		UI.Update();

		UIRender(UI, spheres);

		static int imageWidth, imageHeight;
		glfwGetFramebufferSize(UI.window, &imageWidth, &imageHeight);

		glViewport(0, 0, imageWidth, imageHeight);
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		static int lastW = 1920, lastH = 1080;
		if (imageWidth != lastW || imageHeight != lastH) {
			lastW = imageWidth, lastH = imageHeight;

			screen.Update(imageWidth, imageHeight);
			image.Update(imageWidth, imageHeight);
		}

		image.BindImage(0, GL_WRITE_ONLY);
		computeShader.Use();

		
		computeShader.SetInt("nSphere", spheres.size());

		computeShader.SetInt("image", image.imageUnit);
		computeShader.SetFloat("vFov", fov * M_PI / 180);
		computeShader.Dispatch(imageWidth, imageHeight, 16, 16);

		image.BindImage(0, GL_READ_ONLY);
		screen.BindImage(1, GL_WRITE_ONLY);
		postProcess.BoxBlur(image, screen, kernelRadius);

		screen.BindImage(0, GL_READ_WRITE);
		postProcess.Dither(screen, ditherStrength, noiseSteps);

		screen.BindTexture(0);
		screenQuad.Draw(0);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(UI.window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(UI.window);
	glfwTerminate();

	return 0;
}
