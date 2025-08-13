#pragma once
#include "shader.h"

class ComputeShader : public Shader {
public:
	ComputeShader(const char* path);
	ComputeShader(const std::vector<std::string>& pathList);

	void Reload() override;

	void Attach(const char* path);

	void Dispatch(int res, int numThread);

	void Dispatch(int resX, int resY, int numThreadX, int numThreadY);

	void Dispatch(int resX, int resY, int resZ, int numThreadX, int numThreadY, int numThreadZ) const;

private:
	const char* path;
	std::vector<std::string> pathList;
};