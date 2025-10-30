#pragma once
#include "OpenGL.h"
#include "MathInput.h"

import Vega;



class MathLayer : public Vega::Layer {
public:
	void OnAttach() {

		_shader = new Vega::Shader("defaults/fullScreenQuad.vert", "mathTest/sphericalSources.frag");
		Vega::Systems::Application()->AttachLayer<Vega::ScreenQuad>(_shader);

		_canvas = Vega::Systems::Gui()->AttachCanvas<InputCanvas>("Ole", &_data);

	}

	void OnUpdate() {

		if (Vega::Keys::Pressed(Vega::Key::R, Vega::KeyMod::ModCtrl))
			_shader->Reload();

		_shader->SetVariable("range", _data.range);
		_shader->SetVariable("a", _data.a);
		_shader->SetVariable("wavelength", _data.wl);
		_shader->SetVariable("intensity", _data.intensity);
		_shader->SetVariable("gamma", _data.gamma);
		_shader->SetVariable("L", _data.L);
		_shader->SetVariable("n", _data.n);
		_shader->SetVariable("time", (float)Vega::Timer::TimeS());
	}

private:
	MathData _data{};
	InputCanvas* _canvas;
	Vega::Shader* _shader;
};


