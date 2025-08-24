#pragma once
#include "Shader.h"

namespace Vega {

	class ComputeShader : public Shader {
	public:
		ComputeShader(const char* path);
		ComputeShader(const std::vector<const char*>& pathList);

		void Reload() override;

		void Attach(const char* path);

		void Dispatch1D(int res, int numThread);

		void Dispatch2D(int resX, int resY, int numThreadX, int numThreadY);

		void Dispatch3D(int resX, int resY, int resZ, int numThreadX, int numThreadY, int numThreadZ);

	private:
		std::vector<const char*> _pathList;
	};

}