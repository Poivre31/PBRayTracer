#pragma once
#include "scene.h"
#include <iostream>
#include <fstream>


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

void Scene::RandomScene(int nObjects) {
	const int nPrimitives = 7;
	totalCount = nObjects;
	for (int i = 1; i < nPrimitives; i++)
	{
		counts[i] = 0;
	}

	objects.resize(nObjects);
	for (int i = 0; i < nObjects; i++)
	{
		objects[i].transform.position = { randF(-1.f, 1.f) ,randF(-1.f, 1.f) ,randF(-1.f, 1.f) };
		objects[i].transform.scale = { randF(.02, .1),randF(.02, .1),randF(.02, .1) };
		objects[i].transform.rotation = { randF(0, M_PI) , randF(0, 2 * M_PI) };

		objects[i].material.color = { randF(0,1),randF(0,1) ,randF(0,1) ,1 };

		objects[i].type = rand() % nPrimitives;
		counts[objects[i].type]++;
	}

	selectedIndex = -1;
	selectedType = -1;
}

void Scene::AddObject(Object object) {
	selectedIndex = totalCount;
	selectedType = object.type;

	objects.push_back(object);
	totalCount++;
	counts[object.type]++;
}

void Scene::RemoveObject(int index) {
	objects.erase(objects.begin() + index);

	totalCount--;
	counts[objects[index].type]--;

	if (index == selectedIndex) {
		selectedIndex = -1;
		selectedType = -1;
	}
}

void Scene::Clear() {
	const int nPrimitives = 7;
	totalCount = 0;
	for (int i = 0; i < nPrimitives; i++)
	{
		counts[i] = 0;
	}
	objects.clear();
	selectedIndex = -1;
	selectedType = -1;
}

void Scene::ParseObjects() {
	int baseIndices[7]{};
	for (int i = 1; i < 7; i++)
	{
		baseIndices[i] = baseIndices[i - 1] + counts[i - 1];
	}

	int i[7]{};
	for (Object object: objects)
	{
		int index = i[object.type] + baseIndices[object.type];
		transforms[index] = object.transform;
		colors[index] = object.material.color;
		i[object.type]++;
	}

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, transformsSSBO);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, transformsSSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(transforms), transforms, GL_DYNAMIC_READ);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, colorsSSBO);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, colorsSSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(colors), colors, GL_DYNAMIC_READ);

	rtShader->SetInt("count.sphere", counts[ObjectType::sphere]);
	rtShader->SetInt("count.cube", counts[ObjectType::cube]);
	rtShader->SetInt("count.plane", counts[ObjectType::plane]);
	rtShader->SetInt("count.circle", counts[ObjectType::circle]);
	rtShader->SetInt("count.cylinder", counts[ObjectType::cylinder]);
	rtShader->SetInt("count.cone", counts[ObjectType::cone]);
	rtShader->SetInt("count.pyramid", counts[ObjectType::pyramid]);
}


void Scene::SetEditMode(int mode) {
	rtShader->SetInt("editMode", mode);
	editMode = mode;
}

void Scene::SaveScene(Renderer& UI) {
	std::ofstream saveFile;

	saveFile.open("saves/save1.txt");
	saveFile << "hello\n";
	saveFile.close();

	//OpenFile(UI, "All files");
}