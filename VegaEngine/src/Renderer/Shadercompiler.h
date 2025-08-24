#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include "OpenGL.h"

GLuint CompileShader(unsigned int type, const std::string& source);

GLuint CreateComputeProgram(const std::vector<const char*>& path);

GLuint CreateProgram(const char* vertPath, const char* fragPath);