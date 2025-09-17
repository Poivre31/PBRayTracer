module;
#include "OpenGL.h"
export module Core:Shader;
import :ShaderCompiler;
import std;
import Math;
#pragma once

export namespace Vega {

	enum VegaType {
		VegaInt,
		VegaFloat,
	};

	struct ShaderVariable {
		const char* variableName;
		int count;
	};

	struct ShaderFloat : public ShaderVariable {
		float* adress;
	};

	struct ShaderInt : public ShaderVariable {
		int* adress;
	};

	class Shader {
	public:
		Shader(const char* pathVertex, const char* pathFrag);
		~Shader();

		virtual void Reload();
		void Use() const;

		GLuint GetID();
		void SetID(GLuint ID);

		void SetInt(const char* variable, int value);
		void SetInt2(const char* variable, int a, int b);
		void SetInt2(const char* variable, std::array<int,2> vec);
		void SetInt3(const char* variable, int a, int b, int c);
		void SetInt3(const char* variable, std::array<int, 3> vec);

		void SetFloat(const char* variable, float value);
		void SetFloat2(const char* variable, float a, float b);
		void SetFloat2(const char* variable, std::array<float, 2> vec);
		void SetFloat3(const char* variable, float a, float b, float c);
		void SetFloat3(const char* variable, std::array<float, 3> vec);

		void SetMat3x3(const char* variable, const Math::Mat3x3f& matrix, bool transpose = GL_TRUE);
		//void AttachFloatRef(const char* variable, float* data, int count);

		//void AttachIntRef(const char* variable, int* data, int count);

		//void UpdateUniforms();

	protected:
		Shader() = default;

	private:
		GLuint _ID = 0;
		const char* _pathVertex = nullptr;
		const char* _pathFrag = nullptr;
		std::vector<ShaderFloat> _floatVariables;
		std::vector<ShaderInt> _intVariables;
	};

}