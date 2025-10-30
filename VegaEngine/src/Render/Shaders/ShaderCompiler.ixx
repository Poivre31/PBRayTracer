module;
#include "OpenGL.h"
export module Render:ShaderCompiler;
import std;

namespace Vega {

	export GLuint CompileShader(unsigned int type, const char* source);

	export GLuint CreateComputeProgram(const std::vector<std::string>& path);

	export GLuint CreateProgram(const char* vertPath, const char* fragPath);

}