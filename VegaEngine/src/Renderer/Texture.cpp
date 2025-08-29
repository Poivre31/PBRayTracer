#include "Texture.h"

namespace Vega {

		Texture::Texture(TextureData textureData) : _data(textureData) {
			SetTexture(textureData);
		}

		TextureData Texture::GetData() {
			return _data;
		}

		GLuint Texture::GetID() {
			return _id;
		}

		void Texture::Update(GLuint newWidth, GLuint newHeight) {
			_data.width = newWidth;
			_data.height = newHeight;
			SetTexture(_data);
		}

		void Texture::Delete() {
			glDeleteTextures(1, &_id);
			_id = -1;
		}

		void Texture::SetTexture(TextureData data) {
			Delete();
			glGenTextures(1, &_id);
			glBindTexture(GL_TEXTURE_2D, _id);
			glTexStorage2D(GL_TEXTURE_2D, 1, data.type, (GLsizei)data.width, (GLsizei)data.height);
		}
}
