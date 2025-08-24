#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "vec3.h"
#include "renderer.h"
#include "camera.h"
#include "saveSystem.h"

static ColorBuffer colorsBuffer{};
static unsigned int colorsSSBO = 0;

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

void objectInfo(Object& object)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags winFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

	ImGui::SetNextWindowBgAlpha(0.3f);
	ImGui::Begin("Object info");
	{
		ImGui::Text("Object index: %i", 0);
		std::string typeName;
		switch (object.type) {
		case(ObjectType::sphere):
			typeName = "sphere"; break;
		case(ObjectType::cube):
			typeName = "cube"; break;
		case(ObjectType::plane):
			typeName = "plane"; break;
		case(ObjectType::circle):
			typeName = "circle"; break;
		case(ObjectType::cylinder):
			typeName = "cylinder"; break;
		case(ObjectType::cone):
			typeName = "cone"; break;
		case(ObjectType::pyramid):
			typeName = "pyramid"; break;
		}
		ImGui::Separator();
		ImGui::Text("Object type: %s", typeName);
		ImGui::Text("Position: x=%.1f, y=%.1f, z=%.1f", object.transform.position.x, object.transform.position.y, object.transform.position.z);
		ImGui::Separator();
		ImGui::Text("Scale: x=%.1f, y=%.1f, z=%.1f", object.transform.scale.x, object.transform.scale.y, object.transform.scale.z);
		ImGui::Separator();
		ImGui::Text("Rotation: theta=%.1f, phi=%.1f", object.transform.rotation.x, object.transform.rotation.y);
		ImGui::Separator();
		ImGui::Text("Color: r=%.1f, g=%.1f, b=%.1f", object.material.color.x, object.material.color.y, object.material.color.z);
	}
	ImGui::End();
}

void objectManager(Scene& scene)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags winFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

	static int objectCount = 0;
	static int objectType = 0;
	static Object baby{};

	ImGui::Begin("Object Manager");
	{
		if (ImGui::Button("Clear scene")) {
			scene.Clear();
		}
		if (ImGui::Button("Generate random scene")) {
			scene.RandomScene(objectCount);
		}
		ImGui::SliderInt("Number of objects", &objectCount, 0, 1024);

		ImGui::Separator();
		ImGui::Text("Object creator");

		ImGui::DragFloat3("Position", (float*)&baby.transform.position, .1, -100, 100);
		ImGui::DragFloat3("Scale", (float*)&baby.transform.scale, .1, 0, 100);
		ImGui::SliderFloat2("Rotation", (float*)&baby.transform.rotation, 0, 360);

		ImGui::Combo("Object type", &baby.type, "Sphere\0Cube\0Plane\0Circle\0Cylinder\0Cone\0Pyramid");

		ImGui::ColorEdit3("Color", (float*)&baby.material.color, ImGuiColorEditFlags_Float);

		if (ImGui::Button("Add object")) scene.AddObject(baby);

		ImGui::Separator();

		if (scene.selectedIndex != -1) {
			Object* object = &scene.objects[scene.selectedIndex];
			objectType = object->type;
			ImGui::Text("Object editor");

			ImGui::DragFloat3("Edit position", (float*)&object->transform.position, .1, -100, 100);
			ImGui::DragFloat3("Edit scale", (float*)&object->transform.scale, .1, 0, 100);
			ImGui::SliderFloat2("Edit rotation", (float*)&object->transform.rotation, 0, 360);

			if (ImGui::Combo("Edit type", &object->type, "Sphere\0Cube\0Plane\0Circle\0Cylinder\0Cone\0Pyramid")) {
				scene.counts[objectType]--;
				scene.counts[object->type]++;
			}

			ImGui::ColorEdit3("Edit color", (float*)&object->material.color, ImGuiColorEditFlags_Float);

			if (ImGui::Button("Delete object")) scene.RemoveObject(scene.selectedIndex);
		}
	}
	ImGui::End();
}

void UIRender(Renderer& renderer, Scene& scene, Camera& mainCamera) {
	if (renderer.showDemo)
		ImGui::ShowDemoWindow(&renderer.showDemo);

	char sceneName[255]{};

	ImGui::Begin("Debug");
	//ImGui::InputText("Save name: ", sceneName, sizeof(sceneName));
	if (ImGui::Button("Save scene")) scene.SaveScene("ah");
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
		objectInfo(scene.objects[scene.selectedIndex]);
	}

	ImGui::Render();
}