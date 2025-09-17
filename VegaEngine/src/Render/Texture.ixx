module;
#include "OpenGL.h"
export module Core:Texture;

export namespace Vega {

	struct TextureData {
		GLuint width;
		GLuint height;
		GLenum type;
	};

	class Texture {
	public:
		Texture() = default;
		Texture(TextureData textureData) : _data(textureData) {
			SetTexture(textureData);
		}

		TextureData GetData() const {
			return _data;
		}

		GLuint GetID() const {
			return _id;
		}

		void Update(GLuint newWidth, GLuint newHeight) {
			_data.width = newWidth;
			_data.height = newHeight;
			SetTexture(_data);
		}

		void Delete() {
			glDeleteTextures(1, &_id);
			_id = -1;
		}


	private:

		void SetTexture(TextureData data) {
			Delete();
			glGenTextures(1, &_id);
			glBindTexture(GL_TEXTURE_2D, _id);
			glTexStorage2D(GL_TEXTURE_2D, 1, data.type, (GLsizei)data.width, (GLsizei)data.height);
		}

		GLuint _id = -1;
		TextureData _data{};
	};

}
