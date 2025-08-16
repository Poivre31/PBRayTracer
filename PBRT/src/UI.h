#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "vec3.h"
#include "renderer.h"
#include "camera.h"

static ColorBuffer colorsBuffer{};
static unsigned int colorsSSBO = 0;

static void randomSpheres(Scene& scene, int nObjects) {
	scene.RandomScene(nObjects);
	//colorsBuffer = randomColors(nObjects);
	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, colorsSSBO);
	//glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(ColorBuffer), &colorsBuffer);
}

void cameraOverlay(Camera& mainCamera, int nAccumulatedFrames)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags winFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
	{
		const float PAD = 10.0f;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 workPos = viewport->WorkPos;
		ImVec2 winPos;
		winPos.x = (workPos.x + PAD);
		winPos.y = (workPos.y + PAD);
		ImGui::SetNextWindowPos(winPos, ImGuiCond_Always, ImVec2(0, 0));
		winFlags |= ImGuiWindowFlags_NoMove;
	}
	ImGui::SetNextWindowBgAlpha(0.3f);
	ImGui::Begin("Camera data");
	{
		ImGui::Text("Vertical FOV: %.1f", mainCamera.vFov);
		ImGui::Separator();
		ImGui::Text("Position: x=%.1f, y=%.1f, z=%.1f", mainCamera.position.x, mainCamera.position.y, mainCamera.position.z);
		ImGui::Separator();
		Vec3 dir = sph2cart(mainCamera.direction);
		ImGui::Text("Direction: x=%.1f, y=%.1f, z=%.1f", dir.x, dir.y, dir.z);
		ImGui::Separator();
		ImGui::Text("Number of accumulated frames: %i", nAccumulatedFrames);
	}
	ImGui::End();
}

void objectInfo(Transform& object)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags winFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

	ImGui::SetNextWindowBgAlpha(0.3f);
	ImGui::Begin("Object info");
	{
		ImGui::Text("Position: x=%.1f, y=%.1f, z=%.1f", object.position.x, object.position.y, object.position.z);
		ImGui::Separator();
		ImGui::Text("Scale: x=%.1f, y=%.1f, z=%.1f", object.scale.x, object.scale.y, object.scale.z);
		ImGui::Separator();
		ImGui::Text("Rotation: theta=%.1f, phi=%.1f", object.rotation.x, object.rotation.y);
	}
	ImGui::End();
}

void addObject(Scene& scene, float position[3], float scale[3], float rotation[2], int type, float color[3]) {
	Transform object{};
	object.position.x = position[0];
	object.position.y = position[1];
	object.position.z = position[2];
	object.scale.x = scale[0];
	object.scale.y = scale[1];
	object.scale.z = scale[2];
	object.rotation.x = rotation[0];
	object.rotation.y = rotation[1];

	scene.AddObject(object, type, float4{ color[0],color[1],color[2], 1 });
}

void objectManager(Scene& scene)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags winFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

	static float _position[3]{};
	static float _scale[3]{1,1,1};
	static float _rotation[2]{};
	static float _position2[3]{};
	static float _scale2[3]{ 1,1,1 };
	static float _rotation2[2]{};
	static int _objectType;
	static int _objectType2;
	static float _color[3]{ 1,1,1 };
	static float _color2[3]{ 1,1,1 };
	static int objectCount = 0;

	ImGui::Begin("Object Manager");
	{
		if (ImGui::Button("Clear scene")) {
			scene.Clear();
		}
		if (ImGui::Button("Generate random scene")) {
			scene.Clear();
			randomSpheres(scene, objectCount);
		}
		ImGui::SliderInt("Number of objects", &objectCount, 1, 1024);

		ImGui::Separator();
		ImGui::Text("Object creator");
		ImGui::DragFloat3("Position", _position, .1, -100, 100);
		ImGui::DragFloat3("Scale", _scale, .1, 0, 100);
		ImGui::SliderFloat2("Rotation", _rotation, 0, 360);

		ImGui::Combo("Object type", &_objectType, "Sphere\0Cube\0Plane\0Circle\0Cylinder\0Cone\0Pyramid");

		ImGui::ColorEdit3("Color", _color, ImGuiColorEditFlags_Float);

		if(ImGui::Button("Add object")) addObject(scene, _position, _scale, _rotation, _objectType, _color);

		ImGui::Separator();

		if (scene.selectedIndex != -1) {
			Transform* object = scene.FindTransform(scene.selectedIndex, scene.selectedType);
			_position2[0] = object->position.x;
			_position2[1] = object->position.y;
			_position2[2] = object->position.z;
			_scale2[0] = object->scale.x;
			_scale2[1] = object->scale.y;
			_scale2[2] = object->scale.z;
			_rotation2[0] = object->rotation.x;
			_rotation2[1] = object->rotation.y;
			_color2[0] = scene.colors[scene.selectedIndex].x;
			_color2[1] = scene.colors[scene.selectedIndex].y;
			_color2[2] = scene.colors[scene.selectedIndex].z;
			ImGui::Text("Object editor");
			if (ImGui::DragFloat3("Edit position", _position2, .1, -100, 100)) {
				object->position.x = _position2[0];
				object->position.y = _position2[1];
				object->position.z = _position2[2];
			}
			if (ImGui::DragFloat3("Edit scale", _scale2, .1, 0, 100)) {
				object->scale.x = _scale2[0];
				object->scale.y = _scale2[1];
				object->scale.z = _scale2[2];
			}
			if (ImGui::SliderFloat2("Edit rotation", _rotation2, 0, 360)) {
				object->rotation.x = _rotation2[0] * M_PI / 180;
				object->rotation.y = _rotation2[1] * M_PI / 180;
			}
			if (ImGui::Combo("Edit type", &_objectType, "Sphere\0Cube\0Plane\0Circle\0Cylinder\0Cone\0Pyramid")) {
				std::cout << "Type editing not yet implemented" << std::endl;
			}
			if (ImGui::ColorEdit3("Edit color", _color2, ImGuiColorEditFlags_Float)) {
				scene.colors[scene.selectedIndex] = {_color2[0],_color2[1],_color2[2],1};
			}
		}

		scene.ParseObjects();
	}
	ImGui::End();
}

void UIRender(Renderer& renderer, Scene& scene, Camera& mainCamera) {
	if (renderer.showDemo)
		ImGui::ShowDemoWindow(&renderer.showDemo);

	ImGui::Begin("Debug");
	ImGui::Checkbox("Show demo", &renderer.showDemo);
	ImGui::Checkbox("Vsync", &renderer.vsync);
	ImGui::Checkbox("Render", &renderer.doRender);
	if (!renderer.doRender) renderer.vsync = true;
	ImGui::SliderFloat("Dither strength", &renderer.ditherStrength, 0, .1);
	ImGui::SliderInt("GI samples", &scene.GIsamples, 0, 256);
	ImGui::SliderFloat("Bias isotropy", &scene.GIthreshold, 0, 2);
	ImGui::SliderFloat("Variance threshold", &scene.thresh, 0, 2);
	ImGui::Checkbox("Accumulate frames", &scene.accumulate);
	ImGui::SliderFloat3("Light direction", scene.lightDir, -1, 1);
	ImGui::ColorEdit3("Light color", scene.lightColor, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR);
	ImGui::SliderFloat("Light radius", &scene.lightRadius, 0, 1);

	ImGui::Text("Render time: %.3f ms/frame (%.1f FPS)", 1000.0f / renderer.io->Framerate, renderer.io->Framerate);
	ImGui::End();

	cameraOverlay(mainCamera, scene.nAccumulated);
	objectManager(scene);
	if (scene.selectedIndex != -1) {
		objectInfo(*scene.FindTransform(scene.selectedIndex, scene.selectedType));
	}

	ImGui::Render();
}