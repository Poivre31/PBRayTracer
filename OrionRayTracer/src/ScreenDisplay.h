#pragma once
#include <Vega.h>

class ScreenDisplay : public Vega::ScreenQuadDisplay {
public:
	ScreenDisplay() {
		SetShader(new Vega::Shader("res/fullScreenQuad.vert", "res/fullScreenQuad.frag"));
	}
};