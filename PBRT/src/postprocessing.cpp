#include "postprocessing.h"

void PostProcessor::BoxBlur(Texture& imageIn, Texture& imageOut, int kernelRadius) {
	if (imageIn.width != imageOut.width || imageIn.height != imageOut.height) {
		Log::Error("Box blur: image dimensions must match");
	}
	if (imageIn.imageUnit == -1 || imageOut.imageUnit == -1) {
		Log::Error("Box blur: images must be bound to image units");
	}
	if (imageIn.imageUnit == imageOut.imageUnit) {
		Log::Error("Box blur: image units must be different");
	}

	blurShader.Use();

	blurShader.SetInt("kernelRadius", kernelRadius);

	blurShader.SetInt("imageIn", imageIn.imageUnit);
	blurShader.SetInt("imageOut", imageOut.imageUnit);

	blurShader.Dispatch(imageIn.width, imageIn.height, 32, 32);
}

void PostProcessor::FastAA(Texture& imageIn, Texture& imageOut, float AAStrength, float AAThreshold) {
	if (imageIn.width != imageOut.width || imageIn.height != imageOut.height) {
		Log::Error("Box blur: image dimensions must match");
	}
	if (imageIn.imageUnit == -1 || imageOut.imageUnit == -1) {
		Log::Error("Box blur: images must be bound to image units");
	}
	if (imageIn.imageUnit == imageOut.imageUnit) {
		Log::Error("Box blur: image units must be different");
	}

	AAShader.Use();

	AAShader.SetFloat("strength", AAStrength);
	AAShader.SetFloat("threshold", AAThreshold);

	AAShader.SetInt("imageIn", imageIn.imageUnit);
	AAShader.SetInt("imageOut", imageOut.imageUnit);

	AAShader.Dispatch(imageIn.width, imageIn.height, 32, 32);
}

void PostProcessor::Dither(Texture& image, float ditherStrength, int noiseSteps, int seed) {
	if (image.imageUnit == -1) {
		Log::Error("Box blur: images must be bound to image units");
	}
	ditherShader.Use();

	ditherShader.SetFloat("ditherStrength", ditherStrength);
	ditherShader.SetInt("noiseSteps", noiseSteps);
	ditherShader.SetInt("baseSeed", seed);
	ditherShader.SetInt("imageIn", image.imageUnit);
	ditherShader.SetInt("imageOut", image.imageUnit);

	ditherShader.Dispatch(image.width, image.height, 16, 16);
}

void PostProcessor::ReloadShaders() {
	blurShader.Reload();
	AAShader.Reload();
	ditherShader.Reload();
}

//void boxBlur2X(int kernelRadius) {
//	ComputeShader blurShader = ComputeShader("res/shaders/boxBlur.comp");
//
//	downsampleImage(image, halfImage, dataType, imageWidth, imageHeight, what);
//	glBindImageTexture(0, halfImage, 0, GL_FALSE, 0, GL_READ_WRITE, dataType);
//
//	blurShader.Use();
//	blurShader.SetInt("useLerp", true);
//	blurShader.SetInt("kernelRadius", kernelRadius);
//
//
//	blurShader.Use();
//	glBindImageTexture(1, halfScreen, 0, GL_FALSE, 0, GL_WRITE_ONLY, dataType);
//	blurShader.Dispatch(halfWidth, halfHeight, 16, 16);
//	glBindTextureUnit(0, halfScreen);
//
//	upsampleImage(halfImage, image, dataType, imageWidth, imageHeight);
//	glBindImageTexture(0, image, 0, GL_FALSE, 0, GL_READ_WRITE, dataType);
//}