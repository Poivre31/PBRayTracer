module;
#include "OpenGL.h"
export module Render:Shader;
import :ShaderCompiler;
import std;
import Math;

using namespace Vega::Math;

export namespace Vega {

	struct ShaderVariable {
		std::string& variableName;
		int count;
	};

	class Shader {
	public:
		Shader(std::string pathVertex, std::string pathFrag);
		~Shader();

		virtual void Reload();
		void Use() const;

		GLuint GetID();
		void SetID(GLuint ID);

		void SetVariable(std::string name, int value);
		void SetVariable(std::string name, int2& value);
		void SetVariable(std::string name, int3& value);
		void SetVariable(std::string name, int4& value);

		void SetVariable(std::string name, float value);
		void SetVariable(std::string name, float2& value);
		void SetVariable(std::string name, float3& value);
		void SetVariable(std::string name, float4& value);

		void SetInt(std::string name, int value);
		void SetInt2(std::string name, int2 vec);
		void SetInt3(std::string name, int3 vec);
		void SetInt4(std::string name, int4 vec);

		void SetFloat(std::string name, float value);
		void SetFloat2(std::string name, float2 vec);
		void SetFloat3(std::string name, float3 vec);
		void SetFloat4(std::string name, float4 vec);

		void SetMat3x3(std::string name, const Math::Mat3x3f& matrix, bool transpose = GL_TRUE);
		//void AttachFloatRef(std::string& name, float* data, int count);

		//void AttachIntRef(std::string& name, int* data, int count);

		//void UpdateUniforms();

	protected:
		Shader() = default;

	private:
		GLuint _ID = 0;
		std::string _pathVertex;
		std::string _pathFrag;
	};

}