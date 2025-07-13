#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <fstream>
#include <sstream>

int CreateComputeShader(const std::string& path);

int CreateShader(const std::string& fragPath, const std::string& vertexPath);