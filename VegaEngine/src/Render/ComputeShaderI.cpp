module;
#include "OpenGL.h"
module Core;
import :ComputeShader;
import :ShaderCompiler;

namespace Vega {

	ComputeShader::ComputeShader(const std::string& path) {
		_pathList = { path };
		SetID(CreateComputeProgram(_pathList));
	}

	ComputeShader::ComputeShader(const std::vector<std::string>& pathList) : _pathList(pathList) {
		SetID(CreateComputeProgram(_pathList));
	}

	ComputeShader::ComputeShader(const std::string& directory, const std::string& extension) {
		for (const auto& file : std::filesystem::directory_iterator(directory)) {
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

	void ComputeShader::Attach(std::string path) {
		std::ifstream stream(path);
		std::stringstream source;
		std::string line;

		while (getline(stream, line)) {
			source << line << "\n";
		}
		unsigned int shader = CompileShader(GL_COMPUTE_SHADER, source.str());
		glAttachShader(GetID(), shader);
		glLinkProgram(GetID());
		glValidateProgram(GetID());

		glDeleteShader(shader);
	}

	void ComputeShader::Dispatch1D(GLuint res, GLuint numThread) {
		glDispatchCompute((res + numThread - 1) / numThread, 1, 1);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
	}

	void ComputeShader::Dispatch2D(GLuint resX, GLuint resY, GLuint numThreadX, GLuint numThreadY) {
		glDispatchCompute((resX + numThreadX - 1) / numThreadX, (resY + numThreadY - 1) / numThreadY, 1);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
	}

	void ComputeShader::Dispatch3D(GLuint resX, GLuint resY, GLuint resZ, GLuint numThreadX, GLuint numThreadY, GLuint numThreadZ) {
		glDispatchCompute((resX + numThreadX - 1) / numThreadX, (resY + numThreadY - 1) / numThreadY, (resZ + numThreadZ - 1) / numThreadZ);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
	}

}