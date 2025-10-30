module;
#include "OpenGL.h"
export module Render:Shader;
import :ShaderCompiler;
import std;
import Math;



export namespace Vega {

	struct ShaderVariable {
		const char*& variableName;
		int count;
	};

	class Shader {
	public:
		Shader(const char* pathVertex, const char* pathFrag);
		~Shader();

		virtual void Reload();
		void Use() const;

		GLuint GetID();
		void SetID(GLuint ID);

		void SetVariable(const char* name, int value);
		void SetVariable(const char* name, int2& value);
		void SetVariable(const char* name, int3& value);
		void SetVariable(const char* name, int4& value);

		void SetVariable(const char* name, float value);
		void SetVariable(const char* name, float2& value);
		void SetVariable(const char* name, float3& value);
		void SetVariable(const char* name, float4& value);

		void SetVariable(const char* name, double value);

		void SetInt(const char* name, int value);
		void SetInt2(const char* name, int2 vec);
		void SetInt3(const char* name, int3 vec);
		void SetInt4(const char* name, int4 vec);

		void SetFloat(const char* name, float value);
		void SetFloat2(const char* name, float2 vec);
		void SetFloat3(const char* name, float3 vec);
		void SetFloat4(const char* name, float4 vec);

		void SetMat3x3(const char* name, const Mat3x3f& matrix, bool transpose = GL_TRUE);
		//void AttachFloatRef(const char*& name, float* data, int count);

		//void AttachIntRef(const char*& name, int* data, int count);

		//void UpdateUniforms();

	protected:
		Shader() = default;

	private:
		GLuint _ID = 0;
		std::string _pathVertex;
		std::string _pathFrag;
	};

}