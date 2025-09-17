module;
#include "OpenGL.h"
export module Core:ShaderCompiler;
import std;

namespace Vega {

	export GLuint CompileShader(unsigned int type, const std::string& source);

	export GLuint CreateComputeProgram(const std::vector<std::string>& path);

	export GLuint CreateProgram(const std::string& vertPath, const std::string& fragPath);

}