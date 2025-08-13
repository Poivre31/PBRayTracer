#pragma once
#include "mips.h"
#include "texture.h"
#include "log.h"
#include "computeShader.h"

class PostProcessor {
public:
	void BoxBlur(Texture& imageIn, Texture& imageOut, int kernelRadius);

	void FastAA(Texture& imageIn, Texture& imageOut, float AAStrength, float AAThreshold);

	void Dither(Texture& image, float ditherStrength, int noiseSteps, int seed);

	void ReloadShaders();

private:
	ComputeShader blurShader = ComputeShader("res/shaders/boxBlur.comp");
	ComputeShader AAShader = ComputeShader("res/shaders/fastAA.comp");
	ComputeShader ditherShader = ComputeShader("res/shaders/dither.comp");
};