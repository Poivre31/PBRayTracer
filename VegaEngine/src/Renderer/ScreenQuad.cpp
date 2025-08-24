#include "ScreenQuad.h"

namespace Vega {

	ScreenQuadDisplay::ScreenQuadDisplay() {
		_screenQuad = Mesh2D::CreateScreenQuad();
		_shader = nullptr;
	}

	ScreenQuadDisplay::ScreenQuadDisplay(Shader* shader) {
		_screenQuad = Mesh2D::CreateScreenQuad();
		_shader = shader;
	}

	void ScreenQuadDisplay::SetShader(Shader* shader) {
		_shader = shader;
	}

	void ScreenQuadDisplay::OnUpdate() {
		if (!_shader) {
			spdlog::error("No shader set for screen quad");
			return;
		}
		_screenQuad.Draw(_shader);
	}

}