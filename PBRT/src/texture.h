#pragma once
#include "GL/glew.h"

void setTexture(unsigned int& texture, int dataType, unsigned int width, unsigned int height);

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
