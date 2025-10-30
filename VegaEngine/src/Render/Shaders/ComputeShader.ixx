module;
#include "OpenGL.h"
export module Render:ComputeShader;
import :Shader;
import std;

export namespace Vega {

	class ComputeShader : public Shader {
	public:
		ComputeShader() = default;
		ComputeShader(const char* path);
		ComputeShader(std::vector<std::string> pathList);
		ComputeShader(const char* directory, const char* extension);

		virtual ~ComputeShader();

		void Reload() override;

		void Attach(const char* path);

		void Dispatch1D(int res, int numThread);

		void Dispatch2D(int resX, int resY, int numThreadX, int numThreadY);

		void Dispatch3D(int resX, int resY, int resZ, int numThreadX, int numThreadY, int numThreadZ);

	private:
		std::vector<std::string> _pathList;
	};

}