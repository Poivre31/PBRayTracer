#pragma once
#include <fstream>
#include <sstream>
#include <vector>

unsigned int CompileShader(unsigned int type, const std::string& source);

int CreateComputeShader(const std::string& path);
int CreateComputeShader(const std::vector<std::string>& path);

int CreateShader(const std::string& fragPath, const std::string& vertexPath);