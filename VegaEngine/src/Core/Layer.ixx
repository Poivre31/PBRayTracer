module;
#include "OpenGL.h"


export module Core:Layer;
import Utility;
import std;

namespace Vega {

	export class Layer
	{
	public:
		Layer() = default;
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnResize(GLuint width, GLuint height) {}
		virtual void OnUpdate() {}
		virtual void OnPhysicsUpdate(double timeStep) {}
	};

}

