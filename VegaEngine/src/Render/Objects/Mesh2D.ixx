module;
#include "OpenGL.h"
export module Render:Mesh2D;
import :Mesh;
import std;

namespace Vega {
	const static std::vector<float> screenTriPos = { -1.f, -3.f, -1.f, 1.f, 3.f, 1.f };
	const static std::vector<float> screenTriUv = { 0.f, 2.f, 0.f, 0.f, 2.f, 0.f };

	export class Mesh2D : public Mesh {
	public:

		void Create(std::vector<float> vertexPositions, std::vector<float> uvs, GLuint nVertices) {
			_nVertices = nVertices;

			glBindVertexArray(_vertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

			_vertices = std::vector<float>(nVertices * 4);

			for (size_t i = 0; i < nVertices; i++)
			{
				_vertices[4 * i] = vertexPositions[2 * i];
				_vertices[4 * i + 1] = vertexPositions[2 * i + 1];
				_vertices[4 * i + 2] = uvs[2 * i];
				_vertices[4 * i + 3] = uvs[2 * i + 1];
			}

			glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(4 * nVertices * sizeof(float)), &_vertices[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(2 * sizeof(float)));

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		static Mesh2D CreateScreenQuad() {
			Mesh2D mesh = Mesh2D();
			mesh.Create(screenTriPos, screenTriUv, 3);
			return mesh;
		}

	};

}