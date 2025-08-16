#pragma once
#include "mips.h"
#include "texture.h"
#include "log.h"
#include "computeShader.h"
#include "scene.h"

class PostProcessor {
public:
	PostProcessor();

	void BoxBlur(Texture& imageIn, Texture& imageOut, int kernelRadius);

	void FastAA(Texture& imageIn, Texture& imageOut, float AAStrength, float AAThreshold);

	void Dither(Texture& image, float ditherStrength, int noiseSteps, int seed);

	void AccumulateFrames(Texture& frame, Texture& average, int nAccumulated);

	void EstimateVariance(Texture& image1, Texture& image2);
	float GetVariance();

	void DrawTools(Texture& imageIn, Texture& imageOut, Texture& indices, Scene& scene);

	void ReloadShaders();

private:
	ComputeShader blurShader = ComputeShader("res/shaders/boxBlur.comp");
	ComputeShader AAShader = ComputeShader("res/shaders/fastAA.comp");
	ComputeShader ditherShader = ComputeShader("res/shaders/dither.comp");
	ComputeShader accumulateShader = ComputeShader("res/shaders/accumulateFrames.comp");
	ComputeShader varianceShader = ComputeShader("res/shaders/varianceEstimator.comp");
	ComputeShader toolsShader = ComputeShader({
		"res/shaders/buildingTools.comp",
		"res/shaders/drawTools.comp",
		"res/shaders/sphere.comp",
		"res/shaders/cube.comp",
		"res/shaders/cylinder.comp",
		"res/shaders/cone.comp",
		"res/shaders/circle.comp",
		"res/shaders/rotations.comp",
		"res/shaders/transform.comp",
		"res/shaders/rayGeneration.comp"
		});

	unsigned int varianceSSBO = 0;
};