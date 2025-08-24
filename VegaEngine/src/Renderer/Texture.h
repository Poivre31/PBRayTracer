#pragma once
#include "OpenGL.h"

static void setTexture(unsigned int& texture, int dataType, unsigned int width, unsigned int height) {
	glDeleteTextures(1, &texture);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexStorage2D(GL_TEXTURE_2D, 1, dataType, width, height);
}

namespace Vega {

	class Texture {
	public:
		unsigned int textureID;
		unsigned int textureUnit;
		unsigned int imageUnit;
		size_t width;
		size_t height;
		int dataType;

		Texture(size_t width, size_t height, int dataType) : width(width), height(height), dataType(dataType) {
			setTexture(textureID, dataType, width, height);
			textureUnit = -1;
			imageUnit = -1;
		}

		void Update(size_t newWidth, size_t newHeight) {
			width = newWidth;
			height = newHeight;
			setTexture(textureID, dataType, width, height);
		}

		void BindTexture(unsigned int slot) {
			glBindTextureUnit(slot, textureID);
			textureUnit = slot;
		}

		void BindImage(unsigned int slot, int accessMode = GL_READ_WRITE) {
			glBindImageTexture(slot, textureID, 0, GL_FALSE, 0, accessMode, dataType);
			imageUnit = slot;
		}

		void UnbindTexture() {
			textureUnit = -1;
		}

		void UnbindImage() {
			imageUnit = -1;
		}
	};

}
