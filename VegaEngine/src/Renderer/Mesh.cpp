#include "Mesh.h"

namespace Vega {

	Mesh::Mesh() {
		glGenVertexArrays(1, &_vertexArray);
		glGenBuffers(1, &_vertexBuffer);
	}

	void Mesh::Draw(Shader* shader) {
		shader->Use();

		glBindVertexArray(_vertexArray);
		glDrawArrays(GL_TRIANGLES, 0, _nVertices);
	}

}