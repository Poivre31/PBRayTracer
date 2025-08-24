#include "Mesh2D.h"

namespace Vega {

	void Mesh2D::Create(std::vector<float> vertexPositions, std::vector<float> uvs, GLuint nVertices) {
		_nVertices = nVertices;

		glBindVertexArray(_vertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

		_vertices = new float[nVertices * 4];

		for (size_t i = 0; i < nVertices; i++)
		{
			_vertices[4 * i] = vertexPositions[2 * i];
			_vertices[4 * i + 1] = vertexPositions[2 * i + 1];
			_vertices[4 * i + 2] = uvs[2 * i];
			_vertices[4 * i + 3] = uvs[2 * i + 1];
		}

		glBufferData(GL_ARRAY_BUFFER, 4 * nVertices * sizeof(float), _vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const float*)(2 * sizeof(float)));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	Mesh2D Mesh2D::CreateScreenQuad() {
		Mesh2D mesh = Mesh2D();
		mesh.Create({ -1.f, -3.f, -1.f, 1.f, 3.f, 1.f }, { 0.f, -1.f, 0.f, 1.f, 2, 1.f }, 3);
		return mesh;
	}

}