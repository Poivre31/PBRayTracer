#include "mips.h"

void downsampleImage(unsigned int image, unsigned int output, unsigned int dataType, size_t width, size_t height, bool what) {
	ComputeShader shader = ComputeShader("res/shaders/downsample.comp");
	glBindImageTexture(0, image, 0, GL_FALSE, 0, GL_READ_WRITE, dataType);
	glBindImageTexture(1, output, 0, GL_FALSE, 0, GL_READ_WRITE, dataType);
	shader.Use();
	shader.SetInt("what", what);
	shader.Dispatch((width + 1) / 2, (height + 1) / 2, 16, 16);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void upsampleImage(unsigned int image, unsigned int output, unsigned int dataType, size_t width, size_t height) {
	ComputeShader shader = ComputeShader("res/shaders/upsample.comp");
	glBindImageTexture(0, image, 0, GL_FALSE, 0, GL_READ_WRITE, dataType);
	glBindImageTexture(1, output, 0, GL_FALSE, 0, GL_READ_WRITE, dataType);
	shader.Use();
	shader.Dispatch(width, height, 16, 16);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}