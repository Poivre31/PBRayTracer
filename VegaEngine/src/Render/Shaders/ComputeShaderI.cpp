module;
#include "OpenGL.h"
module Render;
import :ComputeShader;
import :ShaderCompiler;

namespace Vega {

	ComputeShader::ComputeShader(const char* path) {
		_pathList = { "res/" + std::string(path) };
		SetID(CreateComputeProgram(_pathList));
	}

	ComputeShader::ComputeShader(std::vector<std::string> pathList) : _pathList(pathList) {
		for (auto& path : _pathList) {
			path = "res/" + path;
		}
		SetID(CreateComputeProgram(_pathList));
	}

	ComputeShader::ComputeShader(const char* directory, const char* extension) {
		for (const auto& file : std::filesystem::directory_iterator("res/" + std::string(directory))) {
			//if (std::any_of(begin(extensions), end(extensions), [file](std::string a) {return a == file.path().extension(); })) {
			if (extension == file.path().extension()) {
				_pathList.push_back(file.path().string());
			}
		}
		SetID(CreateComputeProgram(_pathList));
	}

	ComputeShader::~ComputeShader() = default;

	void ComputeShader::Reload() {
		SetID(CreateComputeProgram(_pathList));
	}

	//void ComputeShader::Attach(std::string path) {
	//	Use();
	//	std::ifstream stream("res/" + path);
	//	std::stringstream source;
	//	std::string line;

	//	while (getline(stream, line)) {
	//		source << line << "\n";
	//	}
	//	unsigned int shader = CompileShader(GL_COMPUTE_SHADER, source.str());
	//	glAttachShader(GetID(), shader);
	//	glLinkProgram(GetID());
	//	glValidateProgram(GetID());

	//	glDeleteShader(shader);
	//}

	void ComputeShader::Dispatch1D(int res, int numThread) {
		Use();
		glDispatchCompute((res + numThread - 1) / numThread, 1, 1);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
	}

	void ComputeShader::Dispatch2D(int resX, int resY, int numThreadX, int numThreadY) {
		Use();
		glDispatchCompute((resX + numThreadX - 1) / numThreadX, (resY + numThreadY - 1) / numThreadY, 1);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
	}

	void ComputeShader::Dispatch3D(int resX, int resY, int resZ, int numThreadX, int numThreadY, int numThreadZ) {
		Use();
		glDispatchCompute((resX + numThreadX - 1) / numThreadX, (resY + numThreadY - 1) / numThreadY, (resZ + numThreadZ - 1) / numThreadZ);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
	}

}