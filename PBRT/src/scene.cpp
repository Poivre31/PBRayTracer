#pragma once
#include "scene.h"

Scene::Scene(ComputeShader& mainShader) {
	rtShader = &mainShader;
}

void Scene::ConnectGPU() {
	glGenBuffers(1, &transformsSSBO);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, transformsSSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(transforms), transforms, GL_DYNAMIC_READ);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, transformsSSBO);

	glGenBuffers(1, &colorsSSBO);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, colorsSSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(colors), colors, GL_DYNAMIC_READ);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, colorsSSBO);
}

void randomTransforms(std::vector<Transform>& transforms, int nElements) {
	transforms.resize(nElements);
	for (int i = 0; i < nElements; i++)
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

void Scene::RandomScene(int nObjects) {
	int nPrimitives = 7;
	count.total = nObjects;
	count.cube = nObjects / nPrimitives;
	count.plane = count.cube;
	count.circle = count.plane;
	count.cylinder = count.circle;
	count.cone = count.cylinder;
	count.pyramid = count.cone;
	count.sphere = nObjects - count.pyramid - count.cone - count.cylinder - count.circle - count.plane - count.cube;

	randomTransforms(spheres, count.sphere);
	randomTransforms(cubes, count.cube);
	randomTransforms(planes, count.plane);
	randomTransforms(circles, count.circle);
	randomTransforms(cylinders, count.cylinder);
	randomTransforms(cones, count.cone);
	randomTransforms(pyramids, count.pyramid);
	selectedIndex = -1;
	selectedType = -1;

	for (size_t i = 0; i < 4096; i++)
	{
		colors[i] = { randF(0,1),randF(0,1) ,randF(0,1) ,1 };
	}


}

void Scene::AddObject(Transform object, int objectType, float4 color) {
	count.total++;
	int index = 0;
	switch (objectType) {
	case(Object::sphere):
		index = count.sphere;
		count.sphere++;
		spheres.push_back(object); break;
	case(Object::cube):
		index = count.sphere + count.cube;
		count.cube++;
		cubes.push_back(object); break;
	case(Object::plane):
		index = count.sphere + count.cube + count.plane;
		count.plane++;
		planes.push_back(object); break;
	case(Object::circle):
		index = count.circle + count.sphere + count.cube + count.plane;
		count.circle++;
		circles.push_back(object); break;
	case(Object::cylinder):
		index = count.cylinder + count.circle + count.sphere + count.cube + count.plane;
		count.cylinder++;
		cylinders.push_back(object); break;
	case(Object::cone):
		index = count.cone + count.cylinder + count.circle + count.sphere + count.cube + count.plane;
		count.cone++;
		cones.push_back(object); break;
	case(Object::pyramid):
		index = count.pyramid + count.cone + count.cylinder + count.circle + count.sphere + count.cube + count.plane;
		count.pyramid++;
		pyramids.push_back(object); break;
	}
	selectedIndex = index;
	selectedType = objectType;

	colors[index] = color;
}

void Scene::RemoveObject(int index, int objectType) {
	count.total--;
	switch (objectType) {
	case(Object::sphere):
		count.sphere--;
		spheres.erase(spheres.begin() + index); break;
	case(Object::cube):
		count.cube--;
		cubes.erase(cubes.begin() + index); break;
	case(Object::plane):
		count.plane--;
		planes.erase(planes.begin() + index); break;
	case(Object::circle):
		count.circle--;
		circles.erase(circles.begin() + index); break;
	case(Object::cylinder):
		count.cylinder--;
		cylinders.erase(cylinders.begin() + index); break;
	case(Object::cone):
		count.cone--;
		cones.erase(cones.begin() + index); break;
	case(Object::pyramid):
		count.pyramid--;
		pyramids.erase(pyramids.begin() + index); break;
	}
	if (index == selectedIndex) {
		selectedIndex = -1;
		selectedType = -1;
	}
}

void Scene::Clear() {
	count = {};
	spheres.clear();
	cubes.clear();
	planes.clear();
	circles.clear();
	cylinders.clear();
	cones.clear();
	pyramids.clear();
	selectedIndex = -1;
	selectedType = -1;
}

void Scene::ParseObjects() {
	int baseIndex = 0;
	for (size_t i = 0; i < count.sphere; i++)
	{
		transforms[i + baseIndex] = spheres[i];
	}
	baseIndex += count.sphere;
	for (size_t i = 0; i < count.cube; i++)
	{
		transforms[i + baseIndex] = cubes[i];
	}
	baseIndex += count.cube;
	for (size_t i = 0; i < count.plane; i++)
	{
		transforms[i + baseIndex] = planes[i];
	}
	baseIndex += count.plane;
	for (size_t i = 0; i < count.circle; i++)
	{
		transforms[i + baseIndex] = circles[i];
	}
	baseIndex += count.circle;
	for (size_t i = 0; i < count.cylinder; i++)
	{
		transforms[i + baseIndex] = cylinders[i];
	}
	baseIndex += count.cylinder;
	for (size_t i = 0; i < count.cone; i++)
	{
		transforms[i + baseIndex] = cones[i];
	}
	baseIndex += count.cone;
	for (size_t i = 0; i < count.pyramid; i++)
	{
		transforms[i + baseIndex] = pyramids[i];
	}
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, transformsSSBO);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, transformsSSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(transforms), transforms, GL_DYNAMIC_READ);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, colorsSSBO);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, colorsSSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(colors), colors, GL_DYNAMIC_READ);

	rtShader->SetInt("count.sphere", count.sphere);
	rtShader->SetInt("count.cube", count.cube);
	rtShader->SetInt("count.plane", count.plane);
	rtShader->SetInt("count.circle", count.circle);
	rtShader->SetInt("count.cylinder", count.cylinder);
	rtShader->SetInt("count.cone", count.cone);
	rtShader->SetInt("count.pyramid", count.pyramid);
}

int Scene::FindSubIndex(int globalIndex) {
	if (globalIndex < count.sphere) return globalIndex;
	globalIndex -= count.sphere;
	if (globalIndex < count.cube) return globalIndex;
	globalIndex -= count.cube;
	if (globalIndex < count.plane) return globalIndex;
	globalIndex -= count.plane;
	if (globalIndex < count.circle) return globalIndex;
	globalIndex -= count.circle;
	if (globalIndex < count.cylinder) return globalIndex;
	globalIndex -= count.cylinder;
	if (globalIndex < count.cone) return globalIndex;
	globalIndex -= count.cone;
	if (globalIndex < count.pyramid) return globalIndex;	
}

Transform* Scene::FindTransform(int globalIndex, int type) {
	int subIndex = FindSubIndex(globalIndex);
	switch (type) {
	case(Object::sphere):
		return &spheres[subIndex];
	case(Object::cube):
		return &cubes[subIndex];
	case(Object::plane):
		return &planes[subIndex];
	case(Object::circle):
		return &circles[subIndex];
	case(Object::cylinder):
		return &cylinders[subIndex];
	case(Object::cone):
		return &cones[subIndex];
	case(Object::pyramid):
		return &pyramids[subIndex];
	}
}


void Scene::SetEditMode(int mode) {
	rtShader->SetInt("editMode", mode);
	editMode = mode;
}