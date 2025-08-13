#include "computeShader.h"

ComputeShader::ComputeShader(const char* path) : path(path) {
	ID = CreateComputeShader(path);
}

ComputeShader::ComputeShader(const std::vector<std::string>& pathList) : pathList(pathList) {
	path = nullptr;
	ID = CreateComputeShader(pathList);
}

void ComputeShader::Reload() {
	if (path) ID = CreateComputeShader(path);
	else ID = CreateComputeShader(pathList);
}

void ComputeShader::Attach(const char* path) {
	std::ifstream stream(path);
	std::stringstream source;
	std::string line;

	while (getline(stream, line)) {
		source << line << "\n";
	}
	unsigned int shader = CompileShader(GL_COMPUTE_SHADER, source.str());
	glAttachShader(ID, shader);
	glLinkProgram(ID);
	glValidateProgram(ID);

	glDeleteShader(shader);
}

void ComputeShader::Dispatch(int res, int numThread) {
	glDispatchCompute((res + numThread - 1) / numThread, 1, 1);
	glMemoryBarrier(GL_ALL_BARRIER_BITS);
}

void ComputeShader::Dispatch(int resX, int resY, int numThreadX, int numThreadY) {
	glDispatchCompute((resX + numThreadX - 1) / numThreadX, (resY + numThreadY - 1) / numThreadY, 1);
	glMemoryBarrier(GL_ALL_BARRIER_BITS);
}

void ComputeShader::Dispatch(int resX, int resY, int resZ, int numThreadX, int numThreadY, int numThreadZ) const {
	glDispatchCompute((resX + numThreadX - 1) / numThreadX, (resY + numThreadY - 1) / numThreadY, (resZ + numThreadZ - 1) / numThreadZ);
	glMemoryBarrier(GL_ALL_BARRIER_BITS);
}