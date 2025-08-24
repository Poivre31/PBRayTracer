#include "ComputeShader.h"


namespace Vega {

	ComputeShader::ComputeShader(const char* path) {
		_pathList = { path };
		_ID = CreateComputeProgram(_pathList);
	}

	ComputeShader::ComputeShader(const std::vector<const char*>& pathList) {
		_pathList = pathList;
		_ID = CreateComputeProgram(_pathList);
	}

	void ComputeShader::Reload() {
		_ID = CreateComputeProgram(_pathList);
	}

	void ComputeShader::Attach(const char* path) {
		std::ifstream stream(path);
		std::stringstream source;
		std::string line;

		while (getline(stream, line)) {
			source << line << "\n";
		}
		unsigned int shader = CompileShader(GL_COMPUTE_SHADER, source.str());
		glAttachShader(_ID, shader);
		glLinkProgram(_ID);
		glValidateProgram(_ID);

		glDeleteShader(shader);
	}

	void ComputeShader::Dispatch1D(int res, int numThread) {
		glDispatchCompute((res + numThread - 1) / numThread, 1, 1);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
	}

	void ComputeShader::Dispatch2D(int resX, int resY, int numThreadX, int numThreadY) {
		glDispatchCompute((resX + numThreadX - 1) / numThreadX, (resY + numThreadY - 1) / numThreadY, 1);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
	}

	void ComputeShader::Dispatch3D(int resX, int resY, int resZ, int numThreadX, int numThreadY, int numThreadZ) {
		glDispatchCompute((resX + numThreadX - 1) / numThreadX, (resY + numThreadY - 1) / numThreadY, (resZ + numThreadZ - 1) / numThreadZ);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
	}

}