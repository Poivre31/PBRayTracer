#pragma once
#include "Mesh.h"

namespace Vega {

	class Mesh2D : public Mesh {
	public:

		void Create(std::vector<float> vertexPositions, std::vector<float> uvs, GLuint nVertices);

		static Mesh2D CreateScreenQuad();

	};

}