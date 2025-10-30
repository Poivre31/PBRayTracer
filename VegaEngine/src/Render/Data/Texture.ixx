module;
#include "OpenGL.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

export module Render:Texture;
import Utility;
import :ImageFormats;

export namespace Vega {

	struct TextureData {
		int height;
		int width;
		GLenum type = Formats::RGBA16F;
	};

	class Texture {
	public:
		Texture() = default;
		Texture(TextureData textureData) : _data(textureData) {
			if (textureData.type != Formats::RGBA16F)
				Log.warn("Only 16bit float rgba format supported for now");
			textureData.type = Formats::RGBA16F;
			SetTexture(textureData);
		}

		// FIX BEHAVIOUR WIUTH TEXTURE MANAGER
		void LoadFromFile(const char* path) {
			Delete();
			int width, height, channels;
			auto* image = (char*)stbi_load(path, &width, &height, &channels, 4);
			if (!image) {
				Log.error("Failed to load texture");
				return;
			}
			_data.width = width;
			_data.height = height;
			_data.type = Formats::RGBA16F;

			glGenTextures(1, &_id);
			glBindTexture(GL_TEXTURE_2D, _id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, _data.width, _data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

			stbi_image_free(image);
		}

		int Width() const {
			return _data.width;
		}

		int Height() const {
			return _data.height;
		}

		TextureData GetData() const {
			return _data;
		}

		GLuint GetID() const {
			return _id;
		}

		void Update(int newWidth, int newHeight) {
			if (_data.width == newWidth && _data.height == newHeight)
				return;
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
