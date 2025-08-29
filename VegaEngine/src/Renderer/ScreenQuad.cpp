#include "ScreenQuad.h"

namespace Vega {

	ScreenQuadDisplay::ScreenQuadDisplay() {
		_screenQuad = Mesh2D::CreateScreenQuad();
	}

	ScreenQuadDisplay::ScreenQuadDisplay(Shader* shader) : _shader(shader) {
		_screenQuad = Mesh2D::CreateScreenQuad();
	}

	void ScreenQuadDisplay::SetShader(Shader* shader) {
		_shader = shader;
	}

	void ScreenQuadDisplay::OnUpdate() {
		if (!_shader) {
			Log::error("No shader set for screen quad");
			return;
		}
		_screenQuad.Draw(_shader);
	}

}