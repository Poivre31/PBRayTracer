module;
#include "OpenGL.h"
export module Core:ComputeShader;
import :Shader;
import std;

export namespace Vega {

	class ComputeShader : public Shader {
	public:
		ComputeShader() = default;
		ComputeShader(const std::string& path);
		ComputeShader(const std::vector<std::string>& pathList);
		ComputeShader(const std::string& directory, const std::string& extension);

		virtual ~ComputeShader();

		void Reload() override;

		void Attach(std::string path);

		void Dispatch1D(GLuint res, GLuint numThread);

		void Dispatch2D(GLuint resX, GLuint resY, GLuint numThreadX, GLuint numThreadY);

		void Dispatch3D(GLuint resX, GLuint resY, GLuint resZ, GLuint numThreadX, GLuint numThreadY, GLuint numThreadZ);

	private:
		std::vector<std::string> _pathList;
	};

}