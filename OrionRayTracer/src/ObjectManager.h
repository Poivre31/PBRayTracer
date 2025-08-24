#pragma once
#include <Vega.h>



class ObjectManagerUI : public Vega::ImGuiInterface {

	void Draw() final {
		ImGui::Begin("Object Manager");

		Vega::Object* object = &Vega::Application::Get()->sphere;

		ImGui::Text("Object editor");

		ImGui::DragFloat3("Edit position", (float*)&object->transform.position, .1, -100, 100);
		ImGui::DragFloat3("Edit scale", (float*)&object->transform.scale, .1, 0, 100);
		ImGui::SliderFloat2("Edit rotation", (float*)&object->transform.rotation, 0, 360);

		ImGui::ColorEdit3("Edit color", (float*)&object->material.color, ImGuiColorEditFlags_Float);
		
		ImGui::End();
	}

};