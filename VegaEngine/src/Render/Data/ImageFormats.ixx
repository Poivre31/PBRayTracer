module;
#include "OpenGL.h"
export module Render:ImageFormats;

export namespace Vega::Formats {
	enum : GLenum {
		RGBA32F = GL_RGBA32F,
		R32F = GL_R32F,
		RGBA16F = GL_RGBA16F,
		R16F = GL_R16F,
		RGBA8UI = GL_RGBA8UI,
		R8UI = GL_R8UI,
		RGBA16UI = GL_RGBA16UI,
		R16UI = GL_R16UI,
		RGBA32UI = GL_RGBA32UI,
		R32UI = GL_R32UI,
	};
}