#pragma once
#include "mathHelper.h"
#include "vec3.h"
#include "renderer.h"
#include "computeShader.h"

struct Camera {
	Vec3 position{ 0.f,0.f,0.f };
	Vec3 direction{ 1.f,M_PI / 2.f,0.f };
	float vFov{ 35 };
};

void updateCamera(Camera& mainCamera, Renderer& UI, Vec3& dir, Vec3& speed, ComputeShader& computeShader);