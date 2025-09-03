#pragma once
#include "OpenGL.h"

namespace Vega {

	struct TextureData {
		GLuint width;
		GLuint height;
		GLenum type;
	};

	class Texture {
	public:
		Texture() = default;
		Texture(TextureData textureData);

		TextureData GetData();
		GLuint GetID();

		void Update(GLuint newWidth, GLuint newHeight);

		void Delete();


	private:

		void SetTexture(TextureData data);

		GLuint _id = -1;
		TextureData _data{};
	};

}
