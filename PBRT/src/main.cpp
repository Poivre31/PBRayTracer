// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).

#include "mainheader.h"
#include "findIntersect.h"

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
	scene.ParseObjects();

	Vec3 dir{ 1,M_PI / 2,0 };
	Vec3 speed{ 0 };
	while (!glfwWindowShouldClose(UI.window))
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.

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
			Transform reference = *scene.FindTransform(scene.selectedIndex, scene.selectedType);
			scene.AddObject(reference, scene.selectedType, scene.colors[scene.selectedIndex]);
			scene.nAccumulated = 0;
		}

		updateCamera(mainCamera, UI, dir, speed, computeShader);

		static int imageWidth, imageHeight;
		UI.Update(imageWidth, imageHeight);

		static int lastW = 1920, lastH = 1080;
		if (imageWidth != lastW || imageHeight != lastH) {
			lastW = imageWidth, lastH = imageHeight;

			screen.Update(imageWidth, imageHeight);
			image.Update(imageWidth, imageHeight);
			lastFrame.Update(imageWidth, imageHeight);
			average.Update(imageWidth, imageHeight);
			indices.Update(imageWidth, imageHeight);

			scene.nAccumulated = 0;
		}

		if (UI.doRender && glfwGetWindowAttrib(UI.window, GLFW_FOCUSED)) {
			if (ImGui::IsKeyDown(ImGuiKey_MouseLeft) && scene.selectedIndex != -1) {
				if (ImGui::IsKeyPressed(ImGuiKey_MouseLeft, false) && scene.editAxis == Axis::none) {
					if (scene.editMode == EditMode::rotation) {
						scene.editAxis = findSelectedPlane(scene, UI, mainCamera);
					}
					else {
						scene.editAxis = findSelectedAxis(scene, UI, mainCamera);
					}

					Transform* object = scene.FindTransform(scene.selectedIndex, scene.selectedType);
					scene.startPos = { object->position.x, object->position.y, object->position.z };
					scene.startScale = { object->scale.x, object->scale.y, object->scale.z };
					scene.startRot = { object->rotation.x, object->rotation.y, 0 };
					scene.startOffset = computeOffset(scene.startPos, UI, mainCamera, scene.editAxis);
					scene.startAngle = findAngle(scene.startPos, UI, mainCamera, scene.editAxis);
				}

				if (scene.editAxis != Axis::none) {
					Transform* object = scene.FindTransform(scene.selectedIndex, scene.selectedType);

					if (scene.editMode == EditMode::translation) {
						Vec3 intersect = projectAxis(scene.startPos, UI, mainCamera, scene.editAxis) - scene.startOffset;

						if (ImGui::IsKeyDown(ImGuiKey_ModCtrl)) {
							float factor = ImGui::IsKeyDown(ImGuiKey_ModShift) ? 4 : 1;
							switch (scene.editAxis) {
							case(Axis::x):
								intersect.x = roundf(factor * intersect.x) / factor; break;
							case(Axis::y):
								intersect.y = roundf(factor * intersect.y) / factor; break;
							case(Axis::z):
								intersect.z = roundf(factor * intersect.z) / factor; break;
							}
						}

						object->position = float4{ intersect.x, intersect.y, intersect.z, 0 };
						scene.ParseObjects();
					}

					else if (scene.editMode == EditMode::scaling) {
						Vec3 scale = { 1,1,1 };
						Vec3 proj = (projectAxis(scene.startPos, UI, mainCamera, scene.editAxis) - scene.startPos) / scene.startOffset;
						switch (scene.editAxis) {
						case(Axis::x):
							scale.x = max(abs(proj.x), .001); break;
						case(Axis::y):
							scale.y = max(abs(proj.y), .001); break;
						case(Axis::z):
							scale.z = max(abs(proj.z), .001); break;
						}

						scale *= scene.startScale;

						if (ImGui::IsKeyDown(ImGuiKey_ModCtrl)) {
							float factor = ImGui::IsKeyDown(ImGuiKey_ModShift) ? 4 : 1;
							switch (scene.editAxis) {
							case(Axis::x):
								scale.x = ceil(factor * scale.x) / factor;
								if (scale.x == 0) scale.x = scene.startScale.x;
								break;
							case(Axis::y):
								scale.y = ceil(factor * scale.y) / factor;
								if (scale.y == 0) scale.y = scene.startScale.y;
								break;
							case(Axis::z):
								scale.z = ceil(factor * scale.z) / factor;
								if (scale.z == 0) scale.z = scene.startScale.z;
								break;
							}
						}

						object->scale = float4{ scale.x, scale.y, scale.z, 0 };
						scene.ParseObjects();
					}

					else if (scene.editMode = EditMode::rotation) {
						float angle = findAngle(scene.startPos, UI, mainCamera, scene.editAxis) - scene.startAngle;

						Vec3 rotation = scene.startRot;
						if (scene.editAxis == Axis::y) {
							rotation.x += angle;
						}
						else if (scene.editAxis == Axis::z) {
							rotation.y += angle;
						}

						object->rotation = float4{ rotation.x, rotation.y, 0, 0 };
						scene.ParseObjects();
					}
				}
			}

			image.BindImage(0, GL_READ_WRITE);
			indices.BindImage(1, GL_READ_WRITE);
			computeShader.Use();
			computeShader.SetInt2("mousePos", UI.io->MousePos.x, UI.height - UI.io->MousePos.y);
			computeShader.SetInt("frameIndex", ImGui::GetFrameCount());
			computeShader.SetInt("GIsamples", scene.GIsamples);
			computeShader.SetFloat("GIthreshold", scene.GIthreshold);
			float lightNorm = sqrt(scene.lightDir[0] * scene.lightDir[0] + scene.lightDir[1] * scene.lightDir[1] + scene.lightDir[2] * scene.lightDir[2]);
			computeShader.SetFloat3("mainLight.direction", scene.lightDir[0] / lightNorm, scene.lightDir[1] / lightNorm, scene.lightDir[2] / lightNorm);
			computeShader.SetFloat3("mainLight.color", scene.lightColor[0], scene.lightColor[1], scene.lightColor[2]);
			computeShader.SetFloat("mainLight.radius", scene.lightRadius);
			computeShader.Dispatch(imageWidth, imageHeight, 8, 8);


			lastFrame.BindImage(1, GL_READ_WRITE);
			average.BindImage(2, GL_READ_WRITE);
			glCopyImageSubData(
				average.textureID, GL_TEXTURE_2D, 0, 0, 0, 0,
				lastFrame.textureID, GL_TEXTURE_2D, 0, 0, 0, 0,
				image.width, image.height, 0
			);

			postProcess.AccumulateFrames(image, average, scene.accumulate? scene.nAccumulated : 0);
			scene.nAccumulated++;

			bool moving = abs(speed.x) > 0 || abs(speed.y) > 0 || abs(speed.z) > 0 || ImGui::IsKeyDown(ImGuiKey_MouseRight);
			bool settingsChanged = ImGui::IsAnyItemActive();
			if (ImGui::IsKeyPressed(ImGuiKey_Space, false) || moving || settingsChanged || scene.editAxis != Axis::none) {
				scene.nAccumulated = 0;
			}

			postProcess.EstimateVariance(average, lastFrame);
			noise = postProcess.GetVariance();

			indices.BindImage(3, GL_READ_WRITE);
			postProcess.DrawTools(average, image, indices, scene);
			screen.BindImage(4, GL_READ_WRITE);
			postProcess.Dither(image, UI.ditherStrength, 0, ImGui::GetFrameCount());

			glCopyImageSubData(
				image.textureID,GL_TEXTURE_2D,0,0,0,0,
				screen.textureID,GL_TEXTURE_2D,0,0,0,0,
				image.width,image.height,0
			);

		}

		screen.BindTexture(0);
		ImGui::Begin("Image data");
		ImGui::Text("SNR: %.3f dB", noise);
		ImGui::End();
		UIRender(UI, scene, mainCamera);
		screenQuad.Draw(UI, 0);
		glCopyImageSubData(
			image.textureID, GL_TEXTURE_2D, 0, 0, 0, 0,
			screen.textureID, GL_TEXTURE_2D, 0, 0, 0, 0,
			image.width, image.height, 0
		);
	}

	UI.Close();
}
