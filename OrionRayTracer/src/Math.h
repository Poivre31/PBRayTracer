#pragma once
#include "OpenGL.h"
#include "MathInput.h"

import Vega;

class MathLayer : public Vega::Layer {
public:
	void OnAttach() {

		_shader = new Vega::Shader("res/defaults/fullScreenQuad.vert", "res/mathTest/sphericalSources.frag");
		Vega::Application::Get()->AttachLayer<Vega::ScreenQuad>(_shader);

		_canvas = Vega::Application::Get()->GetGUI()->AttachCanvas<InputCanvas>();
		_data = _canvas->GetData();

	}

	void OnUpdate() {

		if (ImGui::IsKeyPressed(ImGuiKey_R))
			_shader->Reload();
		_data = _canvas->GetData();
		_shader->SetFloat2("range", _data->range);
		_shader->SetFloat("a", _data->a);
		_shader->SetFloat("wavelength", _data->wl);
		_shader->SetFloat("intensity", _data->intensity);
		_shader->SetFloat("gamma", _data->gamma);
		_shader->SetFloat("L", _data->L);
		_shader->SetInt("n", _data->n);
		_shader->SetFloat("time", (float)Vega::Timer::GetTimeS());

	}

private:
	MathData* _data;
	InputCanvas* _canvas;
	Vega::Shader* _shader;
};


