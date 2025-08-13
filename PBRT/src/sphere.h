#pragma once
#include <vector>
#include "log.h"
#include "mathHelper.h"
#include "floats.h"

struct ColorBuffer {
	float4 color_roughness[1024];
};

//MaterialsBuffer parseMaterials(std::vector<Material>& materials) {
//	if (materials.size() > 16) Log::Error("Max number of materials: 16");
//	MaterialsBuffer buffer;
//	for (size_t i = 0; i < materials.size(); i++)
//	{
//		buffer.materials[i] = materials[i];
//	}
//	return buffer;
//}

ColorBuffer parseColors(std::vector<Color>& colors) {
	ColorBuffer buffer{};
	int n = colors.size();

	for (size_t i = 0; i < n; i++)
	{
		buffer.color_roughness[i].x = colors[i].r;
		buffer.color_roughness[i].y = colors[i].g;
		buffer.color_roughness[i].z = colors[i].b;
		buffer.color_roughness[i].w = .5;
	}
	return buffer;
}

ColorBuffer randomColors(int n) {
	ColorBuffer buffer{};

	for (size_t i = 0; i < n; i++)
	{
		buffer.color_roughness[i].x = randF(0, 1);
		buffer.color_roughness[i].y = randF(0, 1);
		buffer.color_roughness[i].z = randF(0, 1);
		buffer.color_roughness[i].w = randF(0, 1);
	}
	return buffer;
}