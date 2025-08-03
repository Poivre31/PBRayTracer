#pragma once
#include "floats.h"
#include "mathHelper.h"
#include <vector>
#include "GL/glew.h"
#include <GLFW/glfw3.h>

enum Objects {
	sphere = 0,
	cube = 1,
	plane = 2,
	circle = 3,
	cylinder = 4,
	cone = 5,
	pyramid = 6
};

struct ObjectCounts {
	int total;
	int sphere;
	int cube;
	int plane;
	int circle;
	int cylinder;
	int cone;
	int pyramid;
};

struct Transform {
	float4 position;
	float4 scale;
	float4 rotation;
};

struct TransformBuffer {
	float4 position[1024];
	float4 scale[1024];
	float4 rotation[1024];
};

class Scene {
public:
	std::vector<Transform> transforms;
	TransformBuffer transformBuffer{};
	ObjectCounts count{};

	Scene() {};
	Scene(ComputeShader& mainShader) {
		rtShader = &mainShader;
	}

	void ConnectGPU();

	void RandomScene(int nObjects);
	void AddObject(Transform object, int objectType);
	void RemoveObject(int index, int objectType);

	void ParseTransforms();
	
private:
	unsigned int transformsSSBO = 0;
	ComputeShader* rtShader = nullptr;
};

void Scene::ConnectGPU() {
	glGenBuffers(1, &transformsSSBO);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, transformsSSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(TransformBuffer), &transformBuffer, GL_DYNAMIC_READ);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, transformsSSBO);
}

void Scene::RandomScene(int nObjects) {
	int nPrimitives = sizeof(ObjectCounts) / sizeof(int);
	count.total = nObjects;
	count.cube = nObjects / nPrimitives;
	count.plane = count.cube;
	count.circle = count.plane;
	count.cylinder = count.circle;
	count.cone = count.cylinder;
	count.pyramid = count.cone;
	count.sphere = nObjects - count.pyramid - count.cone - count.cylinder - count.circle - count.plane - count.cube;

	transforms.reserve(nObjects);
	for (int i = 0; i < nObjects; i++)
	{
		transforms[i].position.x = randF(-1, 1);
		transforms[i].position.y = randF(-1.f, 1.f);
		transforms[i].position.z = randF(-1.f, 1.f);
		transforms[i].scale.x = randF(.02, .1);
		transforms[i].scale.y = randF(.02, .1);
		transforms[i].scale.z = randF(.02, .1);
		transforms[i].rotation.x = randF(0, M_PI);
		transforms[i].rotation.y = randF(0, 2 * M_PI);
	}
}

void Scene::AddObject(Transform object, int objectType) {
	count.total++;
	switch (objectType) {
	case(sphere):
		count.sphere++; break;
	case(cube):
		count.cube++; break;
	case(plane):
		count.plane++; break;
	case(circle):
		count.circle++; break;
	case(cylinder):
		count.cylinder++; break;
	case(cone):
		count.cone++; break;
	case(pyramid):
		count.pyramid++; break;
	}

	transforms.push_back(object);
}

void Scene::RemoveObject(int index, int objectType) {
	count.total--;
	switch (objectType) {
	case(sphere):
		count.sphere--; break;
	case(cube):
		count.cube--; break;
	case(plane):
		count.plane--; break;
	case(circle):
		count.circle--; break;
	case(cylinder):
		count.cylinder--; break;
	case(cone):
		count.cone--; break;
	case(pyramid):
		count.pyramid--; break;
	}

	transforms.erase(transforms.begin()+index);
}

void Scene::ParseTransforms() {
	for (size_t i = 0; i < count.total; i++)
	{
		transformBuffer.position[i].x = transforms[i].position.x;
		transformBuffer.position[i].y = transforms[i].position.y;
		transformBuffer.position[i].z = transforms[i].position.z;
		transformBuffer.scale[i].x = transforms[i].scale.x;
		transformBuffer.scale[i].y = transforms[i].scale.y;
		transformBuffer.scale[i].z = transforms[i].scale.z;
		transformBuffer.rotation[i].x = transforms[i].rotation.x;
		transformBuffer.rotation[i].y = transforms[i].rotation.y;
	}	
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, transformsSSBO);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(TransformBuffer), &transformBuffer);

	rtShader->SetInt("count.sphere", count.sphere);
	rtShader->SetInt("count.cube", count.cube);
	rtShader->SetInt("count.plane", count.plane);
	rtShader->SetInt("count.circle", count.circle);
	rtShader->SetInt("count.cylinder", count.cylinder);
	rtShader->SetInt("count.cone", count.cone);
	rtShader->SetInt("count.pyramid", count.pyramid);
}


