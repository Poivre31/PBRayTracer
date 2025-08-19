// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).

#include "mainheader.h"
#include "objectEditing.h"

#define M_PI 3.1415926535897932384626433832795

static Camera mainCamera;
static int nSphere = 1;
static Scene scene;
static float noise;

int main(int, char**)
{
	Renderer UI = Renderer("Ray Tracing", 1920, 1080);
	glewInit();
	UI.Setup();

	int dataType = GL_RGBA32F;

	Texture screen = Texture(1920, 1080, dataType);
	Texture image = Texture(1920, 1080, dataType);
	Texture lastFrame = Texture(1920, 1080, dataType);
	Texture average = Texture(1920, 1080, dataType);
	Texture indices = Texture(1920, 1080, GL_R32UI);

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
		"res/shaders/buildingTools.comp" ,
		});
	Shader shader = Shader("res/shaders/fullScreenQuad.vert", "res/shaders/fullScreenQuad.frag");

	ScreenQuad screenQuad = ScreenQuad(&shader);
	PostProcessor postProcess;

	scene = Scene(computeShader);
	scene.mainCamera = &mainCamera;

	scene.ConnectGPU();
	scene.RandomScene(1);
	scene.ParseObjects();

	Vec3 dir{ 1,M_PI / 2,0 };
	Vec3 speed{ 0 };
	while (!glfwWindowShouldClose(UI.window))
	{
		glfwMakeContextCurrent(UI.window);

		if (ImGui::IsKeyDown(ImGuiKey_ModCtrl) && ImGui::IsKeyPressed(ImGuiKey_R, false)) {
			postProcess.ReloadShaders();
			computeShader.Reload();
			screenQuad.Reload();
			scene.nAccumulated = 0;
			std::cout << "Reloaded RayTracing shader" << std::endl;
		}
		//if (ImGui::IsKeyPressed(ImGuiKey_Space, false)) UI.doRender = 1 - UI.doRender;
		if (ImGui::IsKeyPressed(ImGuiKey_G, false)) scene.SetEditMode(0);
		if (ImGui::IsKeyPressed(ImGuiKey_T, false)) scene.SetEditMode(1);
		if (ImGui::IsKeyPressed(ImGuiKey_R, false)) scene.SetEditMode(2);

		bool moving = abs(speed.x) > 0 || abs(speed.y) > 0 || abs(speed.z) > 0 || ImGui::IsKeyDown(ImGuiKey_MouseRight);
		bool settingsChanged = ImGui::IsAnyItemActive();

		if (ImGui::IsMouseClicked(0) && scene.editAxis == Axis::none && !UI.io->WantCaptureMouse) {
			auto [hit, type] = findHitObject(scene, mainCamera, UI);
			if (hit == scene.selectedIndex) {
				scene.selectedIndex = -1;
				scene.selectedType = -1;
			}
			else if (hit != -1) {
				scene.selectedIndex = hit;
				scene.selectedType = type;
			}
		}

		if (ImGui::IsKeyReleased(ImGuiKey_MouseLeft)) {
			scene.editAxis = Axis::none;
		}

		if (ImGui::IsKeyDown(ImGuiKey_ModShift) && ImGui::IsKeyPressed(ImGuiKey_D, false) && scene.selectedIndex != -1) {
			scene.AddObject(scene.objects[scene.selectedIndex]);
			scene.nAccumulated = 0;
		}

		scene.SaveScene(UI);

		updateCamera(mainCamera, UI, dir, speed, computeShader);

		UI.Update(UI.width, UI.height);

		if (UI.width != screen.width || UI.height != screen.height) {
			screen.Update(UI.width, UI.height);
			image.Update(UI.width, UI.height);
			lastFrame.Update(UI.width, UI.height);
			average.Update(UI.width, UI.height);
			indices.Update(UI.width, UI.height);

			scene.nAccumulated = 0;
		}

		if (UI.doRender && glfwGetWindowAttrib(UI.window, GLFW_FOCUSED)) {
			if (ImGui::IsKeyDown(ImGuiKey_MouseLeft) && scene.selectedIndex != -1) {
				ProcessClick(scene, UI, mainCamera);
			}

			scene.ParseObjects();

			image.BindImage(0, GL_READ_WRITE);
			{
				computeShader.Use();
				computeShader.SetInt("image", image.imageUnit);
				computeShader.SetInt2("mousePos", UI.io->MousePos.x, UI.height - UI.io->MousePos.y);
				computeShader.SetInt("frameIndex", ImGui::GetFrameCount());
				computeShader.SetInt("GIsamples", scene.GIsamples);
				computeShader.SetFloat("GIthreshold", scene.GIthreshold);
				float lightNorm = sqrt(scene.lightDir[0] * scene.lightDir[0] + scene.lightDir[1] * scene.lightDir[1] + scene.lightDir[2] * scene.lightDir[2]);
				computeShader.SetFloat3("mainLight.direction", scene.lightDir[0] / lightNorm, scene.lightDir[1] / lightNorm, scene.lightDir[2] / lightNorm);
				computeShader.SetFloat3("mainLight.color", scene.lightColor[0], scene.lightColor[1], scene.lightColor[2]);
				computeShader.SetFloat("mainLight.radius", scene.lightRadius);
			}
			computeShader.Dispatch(UI.width, UI.height, 16, 16);

			lastFrame.BindImage(1, GL_READ_WRITE);
			average.BindImage(2, GL_READ_WRITE);
			glCopyImageSubData(
				average.textureID, GL_TEXTURE_2D, 0, 0, 0, 0,
				lastFrame.textureID, GL_TEXTURE_2D, 0, 0, 0, 0,
				image.width, image.height, 1
			);

			if (ImGui::IsKeyPressed(ImGuiKey_Space, false) || moving || settingsChanged || scene.editAxis != Axis::none) {
				scene.nAccumulated = 0;
			}
			postProcess.AccumulateFrames(image, average, scene.accumulate? scene.nAccumulated : 0);
			scene.nAccumulated++;

			postProcess.EstimateVariance(average, lastFrame);
			noise = postProcess.GetVariance();

			indices.BindImage(3, GL_READ_WRITE);
			postProcess.DrawTools(average, image, indices, scene);
			postProcess.Dither(image, UI.ditherStrength, 0, ImGui::GetFrameCount());
		}

		ImGui::Begin("Image data");
		ImGui::Text("SNR: %.2f dB", noise);
		ImGui::End();
		UIRender(UI, scene, mainCamera);


		if (ImGui::IsKeyPressed(ImGuiKey_Space, false) || moving || settingsChanged || scene.editAxis != Axis::none) {
			scene.nAccumulated = 0;
		}

		screen.BindImage(4, GL_READ_WRITE);
		glCopyImageSubData(
			image.textureID, GL_TEXTURE_2D, 0, 0, 0, 0,
			screen.textureID, GL_TEXTURE_2D, 0, 0, 0, 0,
			image.width, image.height, 1
		);
		screen.BindTexture(0);
		screenQuad.Draw(UI, 0);
	}

	UI.Close();
}
