module;
#include "OpenGL.h"
export module Render:Mesh;
import :Shader;
import std;

export namespace Vega {

	class Mesh {
	public:

		Mesh() {
			glGenVertexArrays(1, &_vertexArray);
			glGenBuffers(1, &_vertexBuffer);
		}

		void Draw(Shader* shader) const {
			shader->Use();

			glBindVertexArray(_vertexArray);
			glDrawArrays(GL_TRIANGLES, 0, (GLsizei)_nVertices);
		}

	protected:
		GLuint _nVertices = 0;
		GLuint _vertexArray = 0;
		GLuint _vertexBuffer = 0;
		std::vector<float> _vertices;
		//float* _vertices = nullptr;
	};

}