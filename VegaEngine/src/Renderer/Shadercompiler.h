#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include "OpenGL.h"

GLuint CompileShader(unsigned int type, const std::string& source);

GLuint CreateComputeProgram(const std::vector<std::string>& path);

GLuint CreateProgram(const std::string& vertPath, const std::string& fragPath);