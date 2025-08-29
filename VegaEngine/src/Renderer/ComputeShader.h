#pragma once
#include "Shader.h"

namespace Vega {

	class ComputeShader : public Shader {
	public:
		ComputeShader(const char* path);
		ComputeShader(const std::vector<const char*>& pathList);
		virtual ~ComputeShader();

		void Reload() override;

		void Attach(const char* path);

		void Dispatch1D(GLuint res, GLuint numThread);

		void Dispatch2D(GLuint resX, GLuint resY, GLuint numThreadX, GLuint numThreadY);

		void Dispatch3D(GLuint resX, GLuint resY, GLuint resZ, GLuint numThreadX, GLuint numThreadY, GLuint numThreadZ);

	private:
		std::vector<const char*> _pathList;
	};

}