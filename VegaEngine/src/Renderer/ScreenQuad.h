#pragma once
#include "Core/Layer.h"
#include "Core/Log.h"
#include "Core/Application.h"
#include "Mesh2D.h"

namespace Vega {

	class ScreenQuadDisplay : public Layer {
	public:
		ScreenQuadDisplay();

		ScreenQuadDisplay(Vega::Shader* shader);

		void SetShader(Vega::Shader* shader);

		void OnUpdate() override;

	private:
		Mesh2D _screenQuad;
		Shader* _shader;
	};

}