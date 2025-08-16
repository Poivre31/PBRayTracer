#pragma once
#include "camera.h"

void updateCamera(Camera& mainCamera, Renderer& UI, Vec3& dir, Vec3& speed, ComputeShader& computeShader) {
	float speedTheta = 0;
	float speedPhi = 0;
	float scalarSpeed = 10;
	float speedDecay = 20;

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
	else if (ImGui::IsKeyDown(ImGuiKey_D) && !ImGui::IsKeyDown(ImGuiKey_ModShift)) speed += (1 - exp(-lerpY)) * scalarSpeed * UI.io->DeltaTime * left;
	if (ImGui::IsKeyDown(ImGuiKey_A)) speed += (1 - exp(-lerpZ)) * scalarSpeed * UI.io->DeltaTime * up;
	else if (ImGui::IsKeyDown(ImGuiKey_E)) speed -= (1 - exp(-lerpZ)) * scalarSpeed * UI.io->DeltaTime * up;

	if (abs(speed.x) < 0.001) speed.x = 0;
	if (abs(speed.y) < 0.001) speed.y = 0;
	if (abs(speed.z) < 0.001) speed.z = 0;

	mainCamera.position += speed * UI.io->DeltaTime;

	computeShader.SetFloat3("mainCamera.position", mainCamera.position.x, mainCamera.position.y, mainCamera.position.z);
	computeShader.SetFloat2("mainCamera.direction", mainCamera.direction.y, mainCamera.direction.z);
	computeShader.SetFloat("mainCamera.vFov", mainCamera.vFov);
}