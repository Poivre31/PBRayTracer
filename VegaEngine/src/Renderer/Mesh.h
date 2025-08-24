#pragma once
#include "Shader.h"

namespace Vega {

	class Mesh {
	public:

		Mesh();

		void Draw(Shader* shader);

	protected:
		GLuint _nVertices = 0;
		GLuint _vertexArray = 0;
		GLuint _vertexBuffer = 0;
		float* _vertices = nullptr;
	};

}