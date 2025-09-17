#pragma once
import Vega;

class ScreenDisplay : public Vega::ScreenQuadDisplay {
public:
	ScreenDisplay() {
		SetShader(new Vega::Shader("res/fullScreenQuad.vert", "res/fullScreenQuad.frag"));
	}
};