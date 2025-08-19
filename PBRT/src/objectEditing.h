#pragma once
#include "scene.h"
#include "findIntersect.h"

void ProcessClick(Scene& scene, Renderer& UI, Camera& mainCamera) {
	if (ImGui::IsKeyPressed(ImGuiKey_MouseLeft, false) && scene.editAxis == Axis::none) {
		if (scene.editMode == EditMode::rotation) {
			scene.editAxis = findSelectedPlane(scene, UI, mainCamera);
		}
		else {
			scene.editAxis = findSelectedAxis(scene, UI, mainCamera);
		}

		Object object = scene.objects[scene.selectedIndex];
		scene.startPos = { object.transform.position.x, object.transform.position.y, object.transform.position.z };
		scene.startScale = { object.transform.scale.x, object.transform.scale.y, object.transform.scale.z };
		scene.startRot = { object.transform.rotation.x, object.transform.rotation.y, 0 };
		scene.startOffset = computeOffset(scene.startPos, UI, mainCamera, scene.editAxis);
		scene.startAngle = findAngle(scene.startPos, UI, mainCamera, scene.editAxis);
	}

	if (scene.editAxis != Axis::none) {
		Object* object = &scene.objects[scene.selectedIndex];

		if (scene.editMode == EditMode::translation) {
			Vec3 intersect = projectAxis(scene.startPos, UI, mainCamera, scene.editAxis) - scene.startOffset;

			if (ImGui::IsKeyDown(ImGuiKey_ModCtrl)) {
				float factor = ImGui::IsKeyDown(ImGuiKey_ModShift) ? 4 : 1;
				switch (scene.editAxis) {
				case(Axis::x):
					if (mainCamera.direction.x != 0) intersect.x = roundf(factor * intersect.x) / factor; break;
				case(Axis::y):
					if (mainCamera.direction.y != 0) intersect.y = roundf(factor * intersect.y) / factor; break;
				case(Axis::z):
					if (mainCamera.direction.z != 0) intersect.z = roundf(factor * intersect.z) / factor; break;
				}
			}

			object->transform.position = float4{ intersect.x, intersect.y, intersect.z, 0 };
		}

		else if (scene.editMode == EditMode::scaling) {
			Vec3 scale = { 1,1,1 };
			Vec3 proj = (projectAxis(scene.startPos, UI, mainCamera, scene.editAxis) - scene.startPos) / scene.startOffset;
			switch (scene.editAxis) {
			case(Axis::x):
				if (mainCamera.direction.x != 0) scale.x = max(abs(proj.x), .001); break;
			case(Axis::y):
				if (mainCamera.direction.y != 0) scale.y = max(abs(proj.y), .001); break;
			case(Axis::z):
				if (mainCamera.direction.z != 0) scale.z = max(abs(proj.z), .001); break;
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

			object->transform.scale = float4{ scale.x, scale.y, scale.z, 0 };
		}

		else if (scene.editMode = EditMode::rotation) {
			float angle = findAngle(scene.startPos, UI, mainCamera, scene.editAxis) - scene.startAngle;

			Vec3 rotation = scene.startRot;
			if (scene.editAxis == Axis::y && mainCamera.direction.y != 0) {
				rotation.x += angle;
			}
			else if (scene.editAxis == Axis::z && mainCamera.direction.z != 0) {
				rotation.y += angle;
			}

			object->transform.rotation = float4{ rotation.x, rotation.y, 0, 0 };
		}

		scene.ParseObjects();
	}
}