#include "ComputeShader.h"


namespace Vega {

	ComputeShader::ComputeShader(const char* path) {
		_pathList = { path };
		SetID(CreateComputeProgram(_pathList));
	}

	ComputeShader::ComputeShader(const std::vector<const char*>& pathList) : _pathList(pathList) {
		SetID(CreateComputeProgram(_pathList));
	}

	ComputeShader::~ComputeShader() = default;

	void ComputeShader::Reload() {
		SetID(CreateComputeProgram(_pathList));
	}

	void ComputeShader::Attach(const char* path) {
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