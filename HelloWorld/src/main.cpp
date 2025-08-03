// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).

#include "mainheader.h"

#define M_PI 3.1415926535897932384626433832795

struct Camera {
	Vec3 position{ 0.f,0.f,0.f };
	Vec3 direction{ 1.f,M_PI / 2.f,0.f };
	float vFov{ 35 };
} mainCamera;

static float fov = 35;
static int kernelRadius = 0;
static bool Vsync = true;
static bool downsampleBlur = false;
static bool showDemo = false;
static float ditherStrength = 0.007f;
static int noiseSteps = 10;
static int nSphere = 1;
static Scene scene;
static ColorBuffer colorsBuffer{};
static unsigned int colorsSSBO = 0;
static bool doRender = true;
static int AAsamples = 1;
static bool AA = false;
static float AAStrength = 1;
static float AAThreshold = 1;

static void randomSpheres(int nSpheres) {
	scene.RandomScene(nSpheres);
	colorsBuffer = randomColors(nSpheres);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, colorsSSBO);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(ColorBuffer), &colorsBuffer);
}

static void Overlay()
{
	static int location = 0;
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags winFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
	{
		const float PAD = 10.0f;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 workPos = viewport->WorkPos;
		ImVec2 winPos;
		winPos.x = (workPos.x + PAD);
		winPos.y = (workPos.y + PAD);
		ImGui::SetNextWindowPos(winPos, ImGuiCond_Always, ImVec2(0,0));
		winFlags |= ImGuiWindowFlags_NoMove;
	}
	ImGui::SetNextWindowBgAlpha(0.3f);
	ImGui::Begin("Camera data");
	{
		ImGui::Text("Vertical FOV: %.1f",mainCamera.vFov);
		ImGui::Separator();
		ImGui::Text("Position: x=%.1f, y=%.1f, z=%.1f", mainCamera.position.x, mainCamera.position.y, mainCamera.position.z);
		ImGui::Separator();
		Vec3 dir = sph2cart(mainCamera.direction);
		ImGui::Text("Direction: x=%.1f, y=%.1f, z=%.1f", dir.x, dir.y, dir.z);
	}
	ImGui::End();
}
static void UIRender(Renderer& renderer) {
	if (showDemo)
		ImGui::ShowDemoWindow(&showDemo);

	ImGui::Begin("Debug");
	if (ImGui::SliderInt("Number of spheres", &nSphere, 1, 1024)) randomSpheres(nSphere); 	scene.ParseTransforms();
	ImGui::Checkbox("Show demo", &showDemo);
	ImGui::Checkbox("Vsync", &renderer.vsync);
	ImGui::Checkbox("Render", &doRender);
	if (!doRender) renderer.vsync = true;
	ImGui::SliderFloat("Dither strength", &ditherStrength, 0, .1);
	ImGui::Text("Render time: %.3f ms/frame (%.1f FPS)", 1000.0f / renderer.io->Framerate, renderer.io->Framerate);
	ImGui::End();

	Overlay();

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

	ComputeShader computeShader = ComputeShader({
		"res/shaders/rayTracing.comp" ,
		"res/shaders/rayGeneration.comp",
		"res/shaders/transform.comp" ,
		"res/shaders/skyShader.comp",
		"res/shaders/rotations.comp",
		"res/shaders/sphere.comp",
		"res/shaders/cylinder.comp",
		"res/shaders/cone.comp",
		"res/shaders/cube.comp",
		"res/shaders/pyramid.comp",
		"res/shaders/plane.comp",
		"res/shaders/circle.comp",
		"res/shaders/intersectPrimitives.comp" , 
		"res/shaders/primitiveNormals.comp" ,
		});
	Shader shader = Shader("res/shaders/fullScreenQuad.vert", "res/shaders/fullScreenQuad.frag");

	ScreenQuad screenQuad = ScreenQuad(&shader);
	PostProcessor postProcess;

	scene = Scene(computeShader);

	scene.ConnectGPU();
	scene.RandomScene(1);
	scene.ParseTransforms();

	glGenBuffers(1, &colorsSSBO);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, colorsSSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(ColorBuffer), &colorsBuffer, GL_DYNAMIC_READ);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, colorsSSBO);

	Vec3 speed{ 0,0,0 };
	float speedTheta = 0;
	float speedPhi = 0;
	Vec3 dir{ 1,M_PI/2,0 };
	float scalarSpeed = 10;
	float speedDecay = 10;
	while (!glfwWindowShouldClose(UI.window))
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.

		glfwMakeContextCurrent(UI.window);
		glGetString(GL_VERSION);
		{
			if (ImGui::IsKeyPressed(ImGuiKey_R, false)) {
				postProcess.ReloadShaders();
				computeShader.Reload();
				screenQuad.Reload();
				std::cout << "Reloaded RayTracing shader" << std::endl;
			}
			if (ImGui::IsKeyPressed(ImGuiKey_Space, false)) {
				doRender = 1 - doRender;
			}
			if (ImGui::IsKeyDown(ImGuiKey_KeypadAdd)) mainCamera.vFov *= 1.01f;
			if (ImGui::IsKeyDown(ImGuiKey_KeypadSubtract)) mainCamera.vFov *= .99f;

			static bool cursorLocked = false;
			if (ImGui::IsKeyDown(ImGuiKey_MouseRight)) {
				glfwSetInputMode(UI.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				if (cursorLocked) {
					speedTheta = UI.io->MouseDelta.y / 1000;
					speedPhi = -UI.io->MouseDelta.x / 1000;
					dir.y += speedTheta;
					dir.y = fmod(dir.y, 2 * M_PI);
					dir.z += speedPhi;
					dir.z = fmod(dir.z, 2 * M_PI);
				}
				else cursorLocked = true;
			}
			else {
				glfwSetInputMode(UI.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				cursorLocked = false;
			}
			mainCamera.direction = dir;

			Vec3 forward = sph2cart(mainCamera.direction);
			Vec3 up = sph2cart(mainCamera.direction + Vec3(0, -M_PI / 2, 0));
			Vec3 left = forward ^ up;
			speed = exp(-speedDecay * UI.io->DeltaTime) * speed;
			static float lerpX = 0;
			static float lerpY = 0;
			static float lerpZ = 0;
			if (ImGui::IsKeyPressed(ImGuiKey_Z, false) || ImGui::IsKeyPressed(ImGuiKey_S, false)) lerpX = 0.1f;
			else lerpX += .1f;
			if (ImGui::IsKeyPressed(ImGuiKey_Q, false) || ImGui::IsKeyPressed(ImGuiKey_D, false)) lerpY = 0.1f;
			else lerpY += .1f;
			if (ImGui::IsKeyPressed(ImGuiKey_ModShift, false) || ImGui::IsKeyPressed(ImGuiKey_ModCtrl, false)) lerpZ = 0.1f;
			else lerpZ += .1f;
			if (ImGui::IsKeyDown(ImGuiKey_Z)) speed += (1 - exp(-lerpX)) * scalarSpeed * UI.io->DeltaTime * forward;
			else if (ImGui::IsKeyDown(ImGuiKey_S)) speed -= (1 - exp(-lerpX)) * scalarSpeed * UI.io->DeltaTime * forward;
			if (ImGui::IsKeyDown(ImGuiKey_Q)) speed -= (1 - exp(-lerpY)) * scalarSpeed * UI.io->DeltaTime * left;
			else if (ImGui::IsKeyDown(ImGuiKey_D)) speed += (1 - exp(-lerpY)) * scalarSpeed * UI.io->DeltaTime * left;
			if (ImGui::IsKeyDown(ImGuiKey_ModShift)) speed += (1 - exp(-lerpZ)) * scalarSpeed * UI.io->DeltaTime * up;
			else if (ImGui::IsKeyDown(ImGuiKey_ModCtrl)) speed -= (1 - exp(-lerpZ)) * scalarSpeed * UI.io->DeltaTime * up;
			mainCamera.position += speed * UI.io->DeltaTime;
		}

		computeShader.SetFloat3("mainCamera.position", mainCamera.position.x, mainCamera.position.y, mainCamera.position.z);
		computeShader.SetFloat2("mainCamera.direction", mainCamera.direction.y, mainCamera.direction.z);
		computeShader.SetFloat("mainCamera.vFov", mainCamera.vFov);
		computeShader.SetInt("nSphere", nSphere);

		UI.Update();

		UIRender(UI);

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

		if (doRender && glfwGetWindowAttrib(UI.window, GLFW_FOCUSED)) {
			image.BindImage(0, GL_READ_WRITE);
			computeShader.Use();

			computeShader.Dispatch(imageWidth, imageHeight, 32, 32);

			//image.BindImage(0, GL_READ_ONLY);
			//screen.BindImage(1, GL_WRITE_ONLY);
			//postProcess.BoxBlur(image, screen, kernelRadius);

			postProcess.Dither(image, ditherStrength, noiseSteps, ImGui::GetFrameCount());
		}

		image.BindTexture(0);
		screenQuad.Draw(0);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(UI.window);
		glFinish();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(UI.window);
	glfwTerminate();
}
