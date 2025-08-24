#include "saveSystem.h"
#include "scene.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>

void Scene::SaveScene(const char* saveName) {
	if (!std::filesystem::is_directory("saves/")) std::filesystem::create_directory("saves/");
	
	std::ofstream saveFile;
	std::string path = std::format("saves/{}.txt",saveName);

	time_t time = std::time(&time);
	tm date = *std::localtime(&time);

	saveFile.open(path);
	saveFile << "--- PBRT FILE SAVE ---\n"
		<< "Scene: " << saveName << "\n"
		<< "Date: " << 1900 + date.tm_year << " " << date.tm_mon + 1 << " " << date.tm_mday << " " << date.tm_hour << " " << date.tm_min << "\n"
		<< "Time: " << time << "\n"
		<< std::endl;

	saveFile.close();
}