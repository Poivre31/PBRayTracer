#pragma once
#include "Shadercompiler.h"
#include <iostream>
#include "OpenGL.h"

namespace Vega {

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

		virtual void Reload();
		void Use() const;

		void SetInt(const char* variable, int value) ;
		void SetInt2(const char* variable, int a, int b);
		void SetInt2(const char* variable, int* adress);
		void SetInt3(const char* variable, int a, int b, int c);
		void SetInt3(const char* variable, int* adress);

		void SetFloat(const char* variable, float value);
		void SetFloat2(const char* variable, float a, float b);
		void SetFloat2(const char* variable, float* adress);
		void SetFloat3(const char* variable, float a, float b, float c);
		void SetFloat3(const char* variable, float* adress);

		//void AttachFloatRef(const char* variable, float* data, int count);

		//void AttachIntRef(const char* variable, int* data, int count);

		//void UpdateUniforms();

	protected:
		Shader() = default;
		GLuint _ID = 0;

	private:
		const char* _pathVertex = nullptr;
		const char* _pathFrag = nullptr;
		std::vector<ShaderFloat> _floatVariables;
		std::vector<ShaderInt> _intVariables;
	};

}