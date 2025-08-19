#include "postprocessing.h"

PostProcessor::PostProcessor() {
	glGenBuffers(1, &varianceSSBO);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, varianceSSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, 0, nullptr, GL_DYNAMIC_READ);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 10, varianceSSBO);
}

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
	ditherShader.SetInt("image", image.imageUnit);

	ditherShader.Dispatch(image.width, image.height, 16, 16);
}

void PostProcessor::AccumulateFrames(Texture& frame, Texture& average, int nAccumulated) {
	if (frame.width != average.width || frame.height != average.height) {
		Log::Error("Accumulate: image dimensions must match");
	}
	if (average.imageUnit == -1 || frame.imageUnit == -1) {
		Log::Error("Accumulate: images must be bound to image units");
	}
	if (frame.imageUnit == average.imageUnit) {
		Log::Error("Accumulate: image units must be different");
	}

	accumulateShader.Use();

	accumulateShader.SetInt("nAccumulatedFrames", nAccumulated);
	accumulateShader.SetInt("frame", frame.imageUnit);
	accumulateShader.SetInt("average", average.imageUnit);

	accumulateShader.Dispatch(frame.width, frame.height, 8, 8);
}

void PostProcessor::EstimateVariance(Texture& image1, Texture& image2) {
	if (image1.width != image2.width || image1.height != image2.height) {
		Log::Error("Accumulate: image dimensions must match");
	}
	if (image2.imageUnit == -1 || image1.imageUnit == -1) {
		Log::Error("Accumulate: images must be bound to image units");
	}
	if (image1.imageUnit == image2.imageUnit) {
		Log::Error("Accumulate: image units must be different");
	}

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, varianceSSBO);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, varianceSSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, 32 * 4 * 4, nullptr, GL_DYNAMIC_READ);

	varianceShader.Use();
	varianceShader.SetInt("image1", image1.imageUnit);
	varianceShader.SetInt("image2", image2.imageUnit);

	varianceShader.Dispatch(1, 16, 64, 1);
}

float PostProcessor::GetVariance() {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, varianceSSBO);
	float4 output[32]{};
	glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, 32 * 4 * 4, &output);
	Vec3 variance{};
	Vec3 mean{};
	for (size_t i = 0; i < 16; i++)
	{
		variance += Vec3(output[i].x, output[i].y, output[i].z);
		mean += Vec3(output[i + 16].x, output[i + 16].y, output[i + 16].z);
	}

	Vec3 SNR = mean * mean / variance;
	float meanSNR = (SNR.x + SNR.y + SNR.z) / 3;

	return 10 * log10(meanSNR) + 20;
}

void PostProcessor::DrawTools(Texture& imageIn, Texture& imageOut, Texture& indices, Scene& scene) {
	if (imageIn.width != imageOut.width || imageIn.height != imageOut.height) {
		Log::Error("Box blur: image dimensions must match");
	}
	if (imageIn.imageUnit == -1 || imageOut.imageUnit == -1) {
		Log::Error("Box blur: images must be bound to image units");
	}

	toolsShader.Use();

	toolsShader.SetInt("imageIn", imageIn.imageUnit);
	toolsShader.SetInt("imageOut", imageOut.imageUnit);
	toolsShader.SetInt("indices", indices.imageUnit);

	toolsShader.SetInt("selectedIndex", scene.selectedIndex);
	toolsShader.SetInt("editMode", scene.editMode);
	toolsShader.SetFloat3("mainCamera.position", scene.mainCamera->position.x, scene.mainCamera->position.y, scene.mainCamera->position.z);
	toolsShader.SetFloat2("mainCamera.direction", scene.mainCamera->direction.y, scene.mainCamera->direction.z);
	toolsShader.SetFloat("mainCamera.vFov", scene.mainCamera->vFov);
	if (scene.selectedIndex != -1) {
		Object& object = scene.objects[scene.selectedIndex];
		toolsShader.SetFloat3("objectPosition", object.transform.position.x, object.transform.position.y, object.transform.position.z);
	}

	toolsShader.Dispatch(imageIn.width, imageIn.height, 8, 8);
}


void PostProcessor::ReloadShaders() {
	blurShader.Reload();
	AAShader.Reload();
	ditherShader.Reload();
	accumulateShader.Reload();
	varianceShader.Reload();
	toolsShader.Reload();
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